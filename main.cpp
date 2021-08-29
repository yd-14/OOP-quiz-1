#include<iostream>
#include<fstream>

struct user_data{
    std::string username;
    std::string password;
    std::string bloodtype;
};

struct request{
    std::string blood_type;
    int quantity;
};

struct sample_info{
    std::string blood_type;
    std::string location;
    std::string donor;
    int quantity;
};

struct site{
    std::string name_site;
    std::string location;
};

class admin{
        user_data curr_admin;

        void check_request();
        void check_list_donors();
        void add_hospitals();
    public:
        admin(user_data t);
        void admin_menu();
};

class user{
        user_data curr_user;
        int noti_num;

        int calc_noti();

        void check_notification();
        void create_request();

    public:
        user(user_data t);
        void user_menu();
};

void user::create_request()
{
    request temp;
    std::cout<<"Enter bloodtype: ";
    std::cin>>temp.blood_type;
    std::cout<<"Enter quantity: ";
    std::cin>>temp.quantity;
    std::fstream file("requestlist.txt", std::ios_base::app);
    file.write((char*) &temp, sizeof(request));
    file.close();
}

admin::admin(user_data t)
{
    curr_admin=t;
}

void admin::check_request()
{
    request temp;
    std::fstream file("requestlist.txt", std::ios_base::app);
    while(!file.eof())
    {
        file.read((char*) &temp, sizeof(request));
        std::cout<<temp.blood_type<<temp.quantity<<std::endl;
    }
    file.close();
}

void admin::check_list_donors()
{
    std::string name;
    std::fstream file("donorlist.txt", std::ios_base::in);
    while (!file.eof())
    {
        file>>name;
        std::cout<<name<<std::endl;
    }
    
}

void admin::admin_menu()
{
    int ch;
    while(1)
    {
        std::cout<<"Enter:\n  1. Check request\n  2. Check donor list\n  3. add hospital\n  4. logout\n choice: ";
        std::cin>>ch;
        switch (ch)
        {
        case 1:
            check_request();
            break;
        case 2:
            check_list_donors();
            break;
        case 3: 
            add_hospitals();
            break;
        case 4:
            return;
        default:
            std::cout<<"Wrong choice!";
        }
    }
}

void admin::add_hospitals()
{
    site temp;
    std::cout<<"Enter name,location";
    std::cin>>temp.name_site>>temp.location;
    std::fstream file("sitelist.txt", std::ios_base::app);
    file.write((char*) &temp, sizeof(request));
    file.close();
}

void user::check_notification()
{
    request temp;
    std::fstream file("requestlist.txt", std::ios_base::app);
    while(!file.eof())
    {
    file.read((char*) &temp, sizeof(request));
    std::cout<<"Blood required of type: "<<temp.blood_type;
    }
    file.close();
}

void create_admin();//
int no_admin();//
void admin_login();//
void user_login();//
void create_user();//

int main()
{
    if(no_admin())
    {
        create_admin();
    }

    while(1)
    {
        std::cout<<"Enter:\n  1. Admin login\n  2. User login\n  3. New User Registration\n  4. Exit\n Choice: ";
        int ch;
        std::cin>>ch;

        switch(ch)
        {
            case 1:
                admin_login();
                break;
            case 2:
                user_login();
                break;
            case 3:
                create_user();
                break;
            case 4:
                return 0;
            default:
                std::cout<<"wrong choice!";
        }
    }
    return 0;
}

void create_admin()
{
    std::fstream all_ad_file;
    user_data temp;
    std::cout<<"Enter Username:";
    std::cin>>temp.username;
    std::cout<<"Enter password:";
    std::cin>>temp.password;
    all_ad_file.open("Admin_record.txt", std::ios_base::app);
    all_ad_file.write((char*) &temp, sizeof(user_data));
    all_ad_file.close();
}

void create_user()
{
    std::fstream all_user_file;
    user_data temp;
    std::cout<<"Enter Username:";
    std::cin>>temp.username;
    std::cout<<"Enter password:";
    std::cin>>temp.password;
    std::cout<<"Enter Bloodgroup:";
    std::cin>>temp.bloodtype;
    all_user_file.open("User_record.txt", std::ios_base::app);
    all_user_file.write((char*) &temp, sizeof(user_data));
    all_user_file.close();
    all_user_file.open("donor_list", std::ios_base::app);
    all_user_file<<temp.username<<" "<<temp.bloodtype<<std::endl;
    all_user_file.close();
}

int no_admin() // return 1 if there is no admin in the system
{
    user_data temp;
    std::fstream admin_file;
    admin_file.open("Admin_record.txt", std::ios_base::in);
    if(admin_file.peek() == std::fstream::traits_type::eof())
        return 1;
    return 0;
}

void admin_login()
{
    std::string Username, Password;
    user_data temp;
    std::fstream admin_file;
    admin_file.open("Admin_record.txt", std::ios_base::in);
    std::cout<<"Enter Username: ";
    std::cin>>Username;
    while(!admin_file.eof())
    {
        admin_file.read((char*) &temp, sizeof(user_data));
        if(temp.username == Username)
        {
            std::cout<<"Enter Password: ";
            std::cin>>Password;
            if(temp.password == Password)
            {
                admin current_admin(temp);
                current_admin.admin_menu();
                return;
            }
        }
    }
    std::cout<<"Wrong Username or Password!";
}

void user_login()
{
    std::string Username, Password;
    user_data temp;
    std::fstream user_file;
    user_file.open("User_record.txt", std::ios_base::in);
    std::cout<<"Enter Username: ";
    std::cin>>Username;
    while(!user_file.eof())
    {
        user_file.read((char*) &temp, sizeof(user_data));
        if(temp.username == Username)
        {
            std::cout<<"Enter Password: ";
            std::cin>>Password;
            if(temp.password == Password)
            {
                user current_user(temp);
                current_user.user_menu();
                return;
            }
        }
    std::cout<<"Wrong Username or Password!";
    }
}

void user::user_menu()
{
    int ch;
    while(1)
    {
        std::cout<<"Enter:\n  1. Check notifications ("<<noti_num<<")\n  2. Send Request\n  3. Logout\n choice: ";
        std::cin>>ch;
        switch (ch)
        {
        case 1:
            check_notification();
            break;
        case 2:
            create_request();
            break;
        case 3: 
            return;
        default:
            std::cout<<"Wrong choice!";
        }
    }
}

user::user(user_data t)
{
    curr_user=t;
    noti_num=calc_noti();
}

int user::calc_noti()
{
    request temp;
    std::string file_name=curr_user.username;
    file_name.append("_notifile.txt");
    std::fstream file;
    file.open(file_name, std::ios_base::in);
    int count=0;
    while(!file.eof())
    {
        file.read((char*) &temp, sizeof(request));
        count++;
    }

    return count-1;
}

