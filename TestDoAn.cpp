
#include<iostream>
#include<string>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
class User
{
protected:
    string Username;
    string Password;

    string Name;
    string Address;
    string Phone;
    string Email;
public:
    string getUsername(){return Username;}
    string getPassword(){return Password;}
    string getName(){return Name;}
    string getAddress(){return Address;}
    string getPhone(){return Phone;}
    string getEmail(){return Email;}
    void setUsername(string _Username){Username = _Username;}
    void setPassword(string _Password){Password = _Password;}
    void setName(string _Name){Name = _Name;}
    void setAddress(string _Address){Address = _Address;}
    void setPhone(string _Phone){Name = _Phone;}
    void setEmail(string _Email){Name = _Email;}
    User(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    {
        Username = _Username;
        Password = _Password;
        Name = _Name;
        Address = _Address;
        Phone =_Phone;
        Email = _Email;
    }
    User(const User &u){
        Username = u.Username;
        Password = u.Password;
        Name = u.Name;
        Address = u.Address;
        Phone = u.Phone;
        Email = u.Email;
    }
    ~User(){}
    virtual void ReadFile(ifstream &FileIn){
        getline(FileIn, Username, ',');
        getline(FileIn, Password);
    }
    virtual void CreateFile(ofstream &FileOut, char *&FileName){
        string str = (string)FileName;
        string strFile = str + ".TXT";
        FileName = new char [strFile.length()+1];
        strcpy (FileName, strFile.c_str());
        if (FileName != NULL)
        {
            FileOut.open(FileName, ios_base::out);
        }
        delete[] FileName;
    }
    virtual void OpenFile(ifstream &FileIn, char *&FileName){
        string str = (string)FileName;
        string strFile = str + ".TXT";
        FileName = new char [strFile.length()+1];
        strcpy (FileName, strFile.c_str());
        if (FileName != NULL)
        {
            FileIn.open(FileName, ios_base::in);
        }
        delete[] FileName;
    }
    virtual void ReadInfomation(ifstream &FileIn){
        getline(FileIn, Name);
        getline(FileIn, Address);
        getline(FileIn, Phone);
        getline(FileIn, Email);
    }
    virtual void DeleteFile(string FileName){
        char c = 34;
        string Del = "del ";
        string FilePath = ".txt";
        string strDel = c + Del + FileName  + FilePath + c;
        char *ChuoiXoa = new char[strDel.length() + 1];
        strcpy(ChuoiXoa, strDel.c_str());
        system(ChuoiXoa);
    }
    virtual void Input(){
        cin.ignore();
        textcolor(3);
        cout << "Nhap thong tin ca nhan " << endl;
        cout << "Ho ten : ";
        textcolor(15);
        getline(cin, Name);
        textcolor(3);
        cout <<"Dia chi: ";
        textcolor(15);
        getline(cin, Address);
        textcolor(3);
        cout <<"So dien thoai: ";
        textcolor(15);
        getline(cin, Phone);
        textcolor(3);
        cout <<"Email: ";
        textcolor(15);
        getline(cin, Email);
    }
};

class Administrators : public User
{
public:
    void ReadFile(ifstream &FileIn){
        User::ReadFile(FileIn);
    }
    void CreateFile(ofstream &FileOut, char *FileName){
        User::CreateFile(FileOut, FileName);
    }
    bool operator ==(Administrators a){
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Administrators(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    :User(_Username, _Password, _Name, _Address, _Phone, _Password){}
};

class Employees : public User
{
public:
    void ReadFile(ifstream &FileIn){
        User::ReadFile(FileIn);
    }
    void Input(){
        User::Input();
    }
    void CreateFile(ofstream &FileOut, char *FileName){
        User::CreateFile(FileOut, FileName);
    }
    bool operator ==(Employees a){
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Employees(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    :User(_Username, _Password, _Name, _Address, _Phone, _Password){}
};

void DangNhapAdmin()
{
	gotoxy(40, 1);
    textcolor(14);
    cout << "\t****************************"<< endl;
    gotoxy(40, 2);
    cout << "\t*    ";
    textcolor(10);
    cout << "DANG NHAP ADMIN       ";
    textcolor(14);
    cout << "*" << endl;
    gotoxy(40, 3);
    cout << "\t****************************" << endl;
}
void DangNhapEmployees()
{
	gotoxy(40, 1);
    textcolor(14);
    cout << "\t****************************" << endl;
    gotoxy(40, 2);
    cout << "\t*    ";
    textcolor(10);
    cout << "DANG NHAP EMPLOYEES   ";
    textcolor(14);
    cout << "*" << endl;
    gotoxy(40, 3);
    cout << "\t****************************" << endl;
}
void MenuAdmin()
{
	gotoxy(40, 1);
    textcolor(14);
    cout << "\t****************MENU****************" << endl;
    cout << "\t    1. Them Employee                " << endl;
    cout << "\t    2. Xoa Employee                 " << endl;
    cout << "\t    3. Tim Employee                 " << endl;
    cout << "\t    4. Cap nhat Employee            " << endl;
    cout << "\t    5. Hien thi thong tin Employee  " << endl;
    cout << "\t    6. Thoat                        " << endl;
    cout << "\t************************************" << endl;
}
void MenuEmployee()
{
    textcolor(14);
    cout << "\t***********MENU EMPLOYEE***********" << endl;
    cout << "\t     1. Xem thong tin tai khoan    " << endl;
    cout << "\t     2. Doi password               " << endl;
    cout << "\t     3. Thoat                      " << endl;
    cout << "\t***********************************" << endl;

}
void MaHoaPassword(char *&MatKhau, char x, int size)
{
    x = 'a';
    size = 0;
    while(x != 13)
    {
        x = getch();
        if(x == 13)
        {
            break;
        }
        if(MatKhau[0] == '\0')
        {
            while(true)
            {
                x = getch();
                if(x != 8) { break; }
            }
        }
        if(x == 8)
        {
            if(size != 0)
            {
                MatKhau[size] = '\0';
                size--;
                cout << "\b \b";
            }
        }
        else
        {
            cout << x;
            MatKhau[size] = x;
            size++;
            Sleep(100);
            cout << "\b \b*";
        }
    }
    MatKhau[size] = '\0';
}
void Login(string &TaiKhoan, char *&MatKhau)
{
    textcolor(3);
    gotoxy(40, 4);
    cout << "\tUser:     ";
    gotoxy(40, 5);
    cout << "\tPin:     ";
    textcolor(15);
    gotoxy(54, 4);
    cin >> TaiKhoan;   
    char x = 'l';
    int size = 0;
    cout << endl;
    textcolor(3);
    
    textcolor(15);
    gotoxy(54, 5);
    MaHoaPassword(MatKhau, x, size);
    cout << endl;
}
bool KiemTraUsernameEmployee(User *x, string _User)
{
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    while (!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);  
        if(_User == x->getUsername())
            return false;
    }
    FileIn.close();
    return true; 
}
bool DangNhapThanhCong(User *x, char *FilePath, string &SaveUsername){
    ifstream FileIn;
    FileIn.open(FilePath, ios_base::in);
    string TaiKhoan;
    char *MatKhau;
    Login(TaiKhoan, MatKhau);
    while(!FileIn.eof())
    {
        x = new User();
        x->ReadFile(FileIn);
        if(x->getUsername() + x->getPassword() == TaiKhoan + " " + MatKhau){
            SaveUsername = TaiKhoan;
            return true;
        }
    }
    FileIn.close();
    return false;
}
void ThemEmployee(User *x)
{
    string _User, _Pass;
    textcolor(3);
    cout << "Nhap Username muon them: ";
    textcolor(15);
    cin >> _User;
    if(KiemTraUsernameEmployee(x, _User) == true)
    {
        textcolor(3);
        cout << "Nhap Password: ";
        textcolor(15);
        cin >> _Pass;
        char *FilePath = new char[_User.length() +1];
        strcpy(FilePath, _User.c_str());

        ofstream FileOut;
        Employees *Emp = new Employees();
        FileOut.open("Employees.TXT", ios_base::app);                          
        FileOut << endl << _User << ", " << _Pass;
        FileOut.close();

        Emp->CreateFile(FileOut, FilePath);
        Emp->Input();
        FileOut << Emp->getName() << endl << Emp->getAddress() << endl << Emp->getPhone() << endl << Emp->getEmail();
        FileOut.close();
        textcolor(12);
        cout << "Them thanh cong !" << endl;
    }
    else
    {
        cout << "Username da ton tai !" << "\n";
    }
}
void XoaEmployee(User *x, string s){
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    ofstream FileOut;
    FileOut.open("EmployeesCopy.txt", ios_base::out);
    int count = 0;
    while(!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);
        if(x->getUsername() != s)
        {
            FileOut << x->getUsername() << "," << x->getPassword() << endl;
        }
        count++;
    }
    FileIn.close();
    FileOut.close();
    system("del Employees.txt");
    char *c = (char *)"Employees";
    x->CreateFile(FileOut, c);
    FileOut.close();
    FileIn.open("EmployeesCopy.txt", ios_base::in);
    FileOut.open("Employees.txt", ios_base::out);
    while(count > 1){
        x = new Employees();
        x->ReadFile(FileIn);
        if(count == 2)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        count--;
    }
    FileIn.close();
    FileOut.close();
    x->DeleteFile(s);
    textcolor(12);
    cout << "Xoa thanh cong !" << endl;
    system("del EmployeesCopy.txt");
}

void TimEmployee(User *x, string Username)
{
    ifstream FileIn;
    char *FileName = new char[Username.length() + 1];
    strcpy(FileName, Username.c_str());
    x = new Employees();
    x->OpenFile(FileIn, FileName);
    x->ReadInfomation(FileIn);
    textcolor(12);
    cout << "Thong tin Employee can tim: " << endl;
    textcolor(11);
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail(); 
    FileIn.close();  
}
void XemThongTinTaiKhoan(User *x, string Username)
{
    ifstream FileIn;
    char *FileName = new char[Username.length() + 1];
    strcpy(FileName, Username.c_str());
    x = new Employees();
    x->OpenFile(FileIn, FileName);
    x->ReadInfomation(FileIn);
    textcolor(11);
    cout << "Thong tin tai khoan" << endl;
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail(); 
    FileIn.close();  
}
void CapNhatEmployee(User *x)
{
    ifstream FileIn;
    ofstream FileOut;
    FileIn.open("Employees.txt", ios_base::in);
    textcolor(3);
    cout << "Nhap Username muon cap nhat: ";
    string strUser;
    textcolor(15);
    cin >> strUser;
    bool KT = false;
    while(!FileIn.eof())
    {
        x = new User();
        x->ReadFile(FileIn);
        if(x->getUsername() == strUser){
            KT = true;
            break;
        }
    }
    FileIn.close();
    if(KT == true)
    {
        textcolor(10);
        cout << "Chon muc ban muon cap nhat: " << endl;
        cout << "1. Ho ten " << endl;
        cout << "2. Dia chi " << endl;
        cout << "3. So dien thoai " << endl;
        cout << "4. Email " << endl;
        int LuaChon;
        textcolor(15);
        cin >> LuaChon;  
        char *FileName = new char[strUser.length() + 1];
        strcpy(FileName, strUser.c_str());
        x = new Employees();
        string Edit;
        if(LuaChon == 1)
        {
            textcolor(3);
            cout << "Nhap ho ten thay doi: ";
            cin.ignore();
            textcolor(15);
            getline(cin, Edit);
            x->OpenFile(FileIn, FileName);
            x->ReadInfomation(FileIn);   
            FileOut.open("NoName.txt", ios_base::out);
            FileOut << Edit << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            x->DeleteFile(strUser);

            char *fileName = new char[strUser.length() + 1];
            strcpy(fileName, strUser.c_str());
            FileIn.open("NoName.txt", ios_base::in);
            x = new Employees();
            x->ReadInfomation(FileIn);
            x->CreateFile(FileOut, fileName);
            FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            textcolor(12);
            cout << "Cap nhat ho ten Employee thanh cong !" << endl;
            x->DeleteFile("NoName");
        }
        else if(LuaChon == 2)
        {
            textcolor(13);
            cout << "Nhap dia chi thay doi: ";
            cin.ignore();
            textcolor(15);
            getline(cin, Edit);
            x->OpenFile(FileIn, FileName);
            x->ReadInfomation(FileIn);   
            FileOut.open("NoName.txt", ios_base::out);
            FileOut << x->getName() << endl << Edit << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            x->DeleteFile(strUser);

            char *fileName = new char[strUser.length() + 1];
            strcpy(fileName, strUser.c_str());
            FileIn.open("NoName.txt", ios_base::in);
            x = new Employees();
            x->ReadInfomation(FileIn);
            x->CreateFile(FileOut, fileName);
            FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            textcolor(12);
            cout << "Cap nhat dia chi Employee thanh cong !" << endl;
            x->DeleteFile("NoName");
        }
        else if(LuaChon == 3)
        {
            textcolor(3);
            cout << "Nhap so dien thoai thay doi: ";
            cin.ignore();
            textcolor(15);
            getline(cin, Edit);
            x->OpenFile(FileIn, FileName);
            x->ReadInfomation(FileIn);   
            FileOut.open("NoName.txt", ios_base::out);
            FileOut << x->getName() << endl << x->getAddress() << endl << Edit << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            x->DeleteFile(strUser);

            char *fileName = new char[strUser.length() + 1];
            strcpy(fileName, strUser.c_str());
            FileIn.open("NoName.txt", ios_base::in);
            x = new Employees();
            x->ReadInfomation(FileIn);
            x->CreateFile(FileOut, fileName);
            FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            textcolor(12);
            cout << "Cap nhat so dien thoai Employee thanh cong !" << endl;
            x->DeleteFile("NoName");
        }
        else if(LuaChon == 4)
        {
            textcolor(3);
            cout << "Nhap email thay doi: ";
            cin.ignore();
            textcolor(15);
            getline(cin, Edit);
            x->OpenFile(FileIn, FileName);
            x->ReadInfomation(FileIn);  
            FileOut.open("NoName.txt", ios_base::out);
            FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << Edit;
            FileIn.close();
            FileOut.close();
            x->DeleteFile(strUser);

            char *fileName = new char[strUser.length() + 1];
            strcpy(fileName, strUser.c_str());
            FileIn.open("NoName.txt", ios_base::in);
            x = new Employees();
            x->ReadInfomation(FileIn);
            x->CreateFile(FileOut, fileName);
            FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
            FileIn.close();
            FileOut.close();
            textcolor(12);
            cout << "Cap nhat email Employee thanh cong !" << endl;
            x->DeleteFile("NoName");
        }
    }
    else
    {
        textcolor(12);
        cout << "Username khong ton tai! " << endl;
    }
}
void HienThiThongTinEmployee(User *x)
{
    ifstream FileIn;
    x = new Employees();
    FileIn.open("Employees.txt", ios_base::in);
    string strUser[100];
    int n = 0;
    while (!FileIn.eof())
    {
        x->ReadFile(FileIn);
        strUser[n] = x->getUsername();
        n++;
    }
    FileIn.close();
    for(int i = 0; i < n; i++){
        textcolor(12);
        cout << "Thong tin " << strUser[i] << ": "<< endl;
        string s = strUser[i];
        char *FileName = new char[s.length() + 1];
        strcpy(FileName, s.c_str());
        x->OpenFile(FileIn, FileName);
        x->ReadInfomation(FileIn);
        textcolor(11);
        cout << "Ho ten: " << x->getName() << endl;
        cout << "Dia chi: " << x->getAddress() << endl;
        cout << "So dien thoai: " << x->getPhone() << endl;
        cout << "Email: " << x->getEmail() << endl;
        cout << endl;
        FileIn.close();
    }
}
void ThucHienDoiMatKhau(User *x, string CurrentPass, string NewPass, string SaveUsername)
{
    ifstream FileIn;
    ofstream FileOut;
    string s = "NoName";
    char *fileName = new char[s.length() + 1];
    strcpy(fileName, s.c_str());
    x->CreateFile(FileOut, fileName);
    FileIn.open("Employees.txt", ios_base::in);
    int count = 0;
    while (!FileIn.eof())
    {
        x->ReadFile(FileIn);
        count++;
    }
    FileIn.close();
    int tmp = count;
    FileIn.open("Employees.txt", ios_base::in);
    while(count > 0)
    {
    x->ReadFile(FileIn);
        if(count == 1)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        count--;
    }
    FileIn.close();
    FileOut.close();
    x->DeleteFile("Employees");
    string s2 = "NoName";
    char *fileName2 = new char[s2.length() + 1];
    strcpy(fileName2, s2.c_str());
    x->OpenFile(FileIn, fileName2);
    FileOut.open("Employees.txt", ios_base::out);
    while(tmp > 0)
    {
        x->ReadFile(FileIn); 
        if(SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword() && tmp == 1)
        {
            FileOut << x->getUsername() << ", " << NewPass;
            break;
        }
        else if(SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword())
        {
            FileOut << x->getUsername() << ", " << NewPass << endl;
        }
        else
        {
            if(tmp == 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword();
                break;
            }
            else if(tmp != 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword() << endl;
            }
            else
            {
                break;
            }
        }
        tmp--;
    }
    textcolor(12);
    cout << "\nDoi mat khau thanh cong !";
    FileIn.close();
    FileOut.close();
    x->DeleteFile("NoName");
}
void DoiMatKhau(User *x)
{
    ifstream FileIn;
    ofstream FileOut;
    char *CurrentPass = new char[50];
    char *NewPass = new char[50];
    char *ConfirmPass = new char[50];
    char c;
    int size = 0;
    string _User;
    textcolor(3);
    cout << "Nhap username hien tai: ";
    textcolor(15);
    cin >> _User;
    textcolor(3);
    cout << "Nhap password hien tai: ";
    textcolor(15);
    MaHoaPassword(CurrentPass, c, size);
    textcolor(3);
    cout << "\nNhap password moi: ";
    textcolor(15);
    MaHoaPassword(NewPass, c, size);
    textcolor(3);
    cout << "\nNhap lai password moi: ";
    textcolor(15);
    MaHoaPassword(ConfirmPass, c, size);
    FileIn.open("Employees.txt", ios_base::in);
    bool XacNhan = false;
    while(!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);
        if(" " + (string)CurrentPass == x->getPassword() && (string)NewPass == (string)ConfirmPass)
        {   
            XacNhan = true;
            break;
        }
    }
    FileIn.close();
    if(XacNhan == false)
    {
        textcolor(12);
        cout << "\nThong tin ban nhap khong chinh xac, ban vui long kiem tra lai !" << endl;
    }
    else
    {
        ThucHienDoiMatKhau(x, CurrentPass, NewPass, _User);
    }
}

void Menu(User *ds[])
{
    while (true)
    {
        system("cls");
        textcolor(12);
        cout << "1. Dang Nhap ADMIN" << endl;
        cout << "2. Dang Nhap EMPLOYEES" << endl;
        textcolor(9);
        cout << "Nhap lua chon" << endl;
        int LuaChon;
        textcolor(15);
        cin >> LuaChon;
        string TaiKhoan;
        char *MatKhau;
        int k;
        string SaveUsername;
        if(LuaChon == 1)
        {
            while (true)
            {
            system("cls");
            DangNhapAdmin();
            ifstream FileIn;
            ofstream FileOut;
            User *x = NULL;
            int n = 0;
            bool Exit = false;
            if(DangNhapThanhCong(x, (char *)"Administrators.txt", SaveUsername))
            {
                while (true)
                {
                    system("cls");
                    MenuAdmin();
                    textcolor(3);
                    cout << "Moi ban chon chuc nang: ";
                    textcolor(15);
                    cin >> k;
                    if(k == 1)
                    {
                        ThemEmployee(x);
                        string s;
                        getch();
                    }
                    else if(k == 2)
                    {
                        string _User;
                        textcolor(3);
                        cout << "Nhap Username muon xoa: ";
                        textcolor(15);
                        cin >> _User;
                        FileIn.open("Employees.txt", ios_base::in);
                        bool TimThay = false;
                        while (!FileIn.eof())
                        {
                            x = new Employees();
                            x->ReadFile(FileIn);
                            if(x->getUsername() == _User)
                            {
                                TimThay = true;
                                break;
                            }               
                        }
                        FileIn.close();
                        if(TimThay == false)
                        {
                            textcolor(12);
                            cout << "Khong tim thay " << _User << " de xoa !" << endl;
                            getch();
                        }
                        else
                        {
                            XoaEmployee(x, _User);
                            getch();
                        }
                        FileOut.close();
                    }
                    else if(k == 3)
                    {
                        string _User;
                        textcolor(3);
                        cout << "Nhap Username muon tim: ";
                        textcolor(15);
                        cin >> _User;
                        FileIn.open("Employees.txt", ios_base::in);
                        bool TimThay = false;
                        while (!FileIn.eof())
                        {
                            x = new Employees();
                            x->ReadFile(FileIn);
                            if(x->getUsername() == _User)
                            {
                                TimThay = true;
                                break;
                            }               
                        }
                        FileIn.close();
                        if(TimThay == false)
                        {
                            textcolor(12);
                            cout << "Khong tim thay Employee !"<< endl;
                            getch();
                        }
                        else
                        {
                            TimEmployee(x, _User);
                            getch();
                        }
                    }
                    else if(k == 4)
                    {
                        CapNhatEmployee(x);
                        getch();
                    }
                    else if(k == 5)
                    {
                        HienThiThongTinEmployee(x);
                        getch();
                    }
                    else if(k == 6)
                    {
                        Exit = true;
                        break;
                    }
                    else
                    {
                        cout << "Lua chon khong hop le ! Ban vui long chon lai !!!" << endl;
                        getch();
                    }
                }
                if(Exit == true) break;
            }
            else
            {
                textcolor(12);
                cout << "Sai tai khoan hoac mat khau!" << endl;
                getch();
            }
            }        
        }
        else if(LuaChon == 2)
        {
            int count = 0;
            bool Exit = false;
            while(true)
            {
                system("cls");
                DangNhapEmployees();
                ifstream FileIn;
                User *x = NULL;
                int n = 0;
                if(DangNhapThanhCong(x, (char *)"Employees.txt", SaveUsername))
                {
                    textcolor(12);
                    cout << "Dang nhap thanh cong !" << endl;
                    char *CurrentPass = new char[50];
                    char *NewPass = new char[50];
                    char c = 'a';
                    int size = 0;
                    ifstream FileIn;
                    ofstream FileOut;
                    textcolor(3);
                    cout << "Ban vui long doi mat khau truoc khi su dung chuong trinh !" << endl;
                    getch();
                    while(true)
                    {
                        system("cls");
                        textcolor(3);
                        cout << "Nhap mat khau hien tai: ";
                        textcolor(15);
                        MaHoaPassword(CurrentPass, c, size);
                        textcolor(3);
                        cout << "\nNhap mat khau moi: ";
                        textcolor(15);
                        MaHoaPassword(NewPass, c, size);
                        if((string)CurrentPass == (string)NewPass)
                        {
                            textcolor(12);
                            cout << "\nTrung mat khau roi thim! Moi thim nhap lai!" << endl;
                            getch();
                        }
                        else break;
                    }
                    FileIn.open("Employees.txt", ios_base::in);
                    bool XacNhan = false;
                    while(!FileIn.eof())
                    {
                        x = new Employees();
                        x->ReadFile(FileIn);
                        if(" " + (string)CurrentPass == x->getPassword())
                        {   
                            XacNhan = true;
                            break;
                        }
                    }
                    FileIn.close();
                    if(XacNhan == false)
                    {
                        textcolor(12);
                        cout << "\nMat khau hien tai khong chinh xac! " << endl;
                        getch();
                    }
                    else
                    {
                        ThucHienDoiMatKhau(x, (string)CurrentPass, (string)NewPass, SaveUsername);
                        getch();
                    }
                    while (true)
                    {
                        system("cls");
                        MenuEmployee();
                        textcolor(3);
                        cout << "Moi ban chon chuc nang: ";
                        textcolor(15);
                        cin >> k;   
                        if(k == 1)
                        {
                            XemThongTinTaiKhoan(x, SaveUsername);
                            getch();
                        }
                        else if(k == 2)
                        {
                            DoiMatKhau(x);
                            getch();
                        }
                        else if(k == 3)
                        {
                            Exit = true;
                            break;
                        }
                    }
                }
                else
                {
                    count++;
                    textcolor(12);
                    cout << "Sai tai khoan hoac mat khau!" << endl;
                }
                if(count == 3) exit(0);
                if(Exit == true) break;
                getch();
            }
        }
        else
        {
            textcolor(12);
            cout << "Lua chon khong hop le!" << endl;
            getch();
        }
    }
}
int main(){
    User *ds[100];
    Menu(ds);
    system("pause");
}
