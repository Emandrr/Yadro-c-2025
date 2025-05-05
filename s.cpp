#include<iostream>
#include<string>
#include <fstream>
#include<vector>
#include<cmath>
#include<algorithm>

struct Table {
    int number;
    unsigned long long money = 0;
    bool is_active;
    std::string client_name;
    long long time = 0;
    long long start_time = 0;
};

std::vector<std::string>clients;
std::vector<std::string>query_clients;
std::vector<Table> tables;



inline bool check_digit(char a)
{
    if (a < 48 || a>57) return false;
    else return true;
}

inline bool check_int(unsigned long long& checked,std::string &error,std::ifstream &file)
{
    std::string buff;
    file >> buff;
    if (buff.size() == 0)
    {
        error.resize(0);
        return false;
    }
    error = buff;
    int count;

    if (buff.size() > 20) return false;
    for (int i = 0;i < buff.size();++i)
    {
        if (!check_digit(buff[i])) return false;
        else checked += (buff[i] - '0');
        if (i + 1 < buff.size()) checked *= 10;
        if (checked < 0) return false;
    }
    return true;
}
bool compare_time(const std::vector<int> &time_1, const std::vector<int>&time_2)
{

    int time_1_min = (time_1[0] * 10 + time_1[1]) * 60 + (time_1[2] * 10 + time_1[3]);
    int time_2_min = (time_2[0] * 10 + time_2[1]) * 60 + (time_2[2] * 10 + time_2[3]);

    if (time_1_min > time_2_min) {
        return false;
    }
    return true;

}

void first_event(std::vector<int>time,std::string name,const std::string &output,const std::vector<int> &start_time,const std::vector<int>&end_time)
{
    std::cout << output << "\n";
    for (int i = 0;i < clients.size();++i)
    {
        if (clients[i] == name)
        {
            std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " YouShallNotPass\n";
            return;
        }
        
    }
    if (!compare_time(start_time, time) || !compare_time(time, end_time))
    {
        std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " NotOpenYet\n";
        return;
    }
    clients.push_back(name);
    query_clients.push_back(name);
}
void second_event(std::vector<int> time, std::string name, int number, const std::string& output, unsigned long long price)
{
    bool flag = false;
    int ind = 0;
    std::cout << output << "\n";
    for (int i = 0;i < clients.size();++i)
    {
        if (clients[i] == name) {
            flag = true;
            ind = i;
            break;
        }
    }
    if (!flag)
    {
        std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " ClientUnknown\n";
        return;
    }
    for (int i = 0;i < tables.size();++i)
    {
        if (tables[i].client_name == name)
        {
            if (!tables[number - 1].is_active)
            {
                std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " PlaceIsBusy\n";
                return;
            }
            else
            {
                tables[i].is_active = true;
                tables[i].client_name = "";
                tables[i].time += (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3])- tables[i].start_time;
                tables[i].money += (std::ceil(double((time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]) - tables[i].start_time) / 60)) * price;
                tables[number-1].is_active = false;
                tables[number-1].client_name = name;
                tables[number - 1].start_time = (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]);
                return;
            }
        }
    }
    if (!tables[number - 1].is_active)
    {
        std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " PlaceIsBusy\n";
        return;
    }
    else
    {
        tables[number - 1].is_active = false;
        tables[number - 1].client_name = name;
        tables[number - 1].start_time = (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]);
    }
    for (int i = 0;i < query_clients.size();++i)
    {
        if (query_clients[i] == name)
        {
            query_clients.erase(query_clients.begin() + i);
        }

    }
}
void third_event(std::vector<int>time, std::string name, const std::string& output)
{
    std::cout << output << "\n";
    for (int i = 0;i < tables.size();++i)
    {
        if (tables[i].is_active)
        {
            std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " ICanWaitNoLonger!\n";
            return; 
        }
    }
    if (query_clients.size() > tables.size())
    {
        std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 11 << ' ' << name << "\n";
        for (int i = 0;i < query_clients.size();++i)
        {
            if (query_clients[i] == name)
            {
                query_clients.erase(query_clients.begin() + i);
                break;
            }

        }
        for (int i = 0;i < clients.size();++i)
        {
            if (clients[i] == name) {
                clients.erase(clients.begin() + i);
                break;
            }
        }
        return;
    }
}
void fourth_event(std::vector<int>time, std::string name, const std::string& output, unsigned long long price)
{
    bool flag = false;
    int ind = 0;
    std::cout << output << "\n";
    for (int i = 0;i < clients.size();++i)
    {
        if (clients[i] == name) {
            flag = true;
            ind = i;
            break;
        }
    }
    if (!flag)
    {
        std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 13 << " ClientUnknown\n";
        return;
    }

    else
    {
        clients.erase(clients.begin() + ind);
        for (int i = 0;i < query_clients.size();++i)
        {
            if (query_clients[i] == name)
            {
                query_clients.erase(query_clients.begin() + i);
                return;
            }

        }
        int number=0;

        for (int i = 0;i < tables.size();++i)
        {
            if (tables[i].client_name == name)
            {
                if (query_clients.size() > 0)
                {

                    tables[i].client_name = query_clients[0];
                    tables[i].time += (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]) - tables[i].start_time;
                    tables[i].money += (std::ceil(double((time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]) - tables[i].start_time) / 60)) * price;
                    tables[i].start_time = (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]);
                    number = i + 1;
                    std::cout << time[0] << time[1] << ":" << time[2] << time[3] << ' ' << 12 << ' ' << query_clients[0] << ' ' << number << "\n";
                    query_clients.erase(query_clients.begin());
                    return;
                }
                else
                {
                    tables[i].is_active = true;
                    tables[i].client_name = "";
                    tables[i].time += (time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]) - tables[i].start_time;
                    tables[i].money += (std::ceil(double((time[0] * 10 + time[1]) * 60 + (time[2] * 10 + time[3]) - tables[i].start_time) / 60)) * price;
                    tables[i].start_time = 0;
                }
            }
        }
    }
}



bool set_time(std::vector<int>& time,std::string &error, std::ifstream &file)
{
    std::string buffer;
    int counter = 0;

    file >> buffer;
    error = buffer;
    if (buffer.size() == 0)
    {
        error.resize(0);
        return false;
    }
    if (buffer.size() != 5) {
        return false;
    }
    
    for (int i = 0;i < 2;++i)
    {
        if (!check_digit(buffer[counter]))
        {
            return false;
        }
        else time.push_back(buffer[counter] - '0');
        counter++;
    }
    if (buffer[counter] != ':') return false;
    counter++;
    for (int i = 0;i < 2;++i)
    {
        if (!check_digit(buffer[counter]))
        {
            return false;
        }
        else time.push_back(buffer[counter] - '0');
        counter++;
    }
    if (time[0] > 2 || (time[0] == 2 && time[1] > 4) || time[2] > 6 || (time[2] == 6 && time[3] > 0)) return false;
    //error.resize(0);
    return true;
}
bool query(std::vector<int> start_time, std::vector<int>end_time, unsigned long long price, unsigned long long razm, std::ifstream& file)
{
    tables.resize(razm);
    std::string buffer;
    for (int i = 0;i < razm;++i)
    {
        tables[i] = { i,0,true };
    }
    bool flag = true;
    std::vector<bool> checkers(5, true);
    std::vector<std::string> errors(4);
    std::vector<int>time;
    unsigned long long choise=0;
    unsigned long long station=0;
    while (flag)
    {
        station = 0;
        choise = 0;
        time.resize(0);

        checkers[0] = set_time(time, errors[0], file);
        if (errors[0].size() == 0) break;
        checkers[1] = check_int(choise, errors[1], file);
        if (choise == 1 || choise == 3 || choise == 4)
        {
            file >> buffer;
            errors[2] = buffer;
            if (!(checkers[0] && checkers[1]))
            {
                std::cout << errors[0] << ' ' << errors[1] << ' ' << errors[2];
                return false;
            }
            if (choise == 1) first_event(time,buffer, errors[0]+' ' + errors[1]+' ' + errors[2], start_time, end_time);
            else if (choise == 4) fourth_event(time,buffer, errors[0]+' ' + errors[1] + ' ' + errors[2],price);
            else if (choise == 3) third_event(time,buffer, errors[0]+' ' + errors[1]+' ' + errors[2]);
        }
        else if (choise == 2)
        {
            file >> buffer;
            errors[2] = buffer;
            checkers[3] = check_int(station,errors[3],file);
            if (!(checkers[0] && checkers[1] && checkers[2]))
            {
                std::cout << errors[0] << ' ' << errors[1] << ' ' << errors[2] << ' ' << errors[3];
                return false;
            }
            second_event(time,buffer,station, errors[0]+' ' + errors[1]+' ' + errors[2]+ ' '+ errors[3], price);
        }
        else
        {
            std::getline(file, buffer);
            std::cout << errors[0] << ' ' << errors[1] << ' ' << buffer;
            return false;
        }
    }
    file.close();
    std::vector<std::string> all_clients;
    for (int i = 0;i < clients.size();++i)
    {
        all_clients.push_back(clients[i]);
    }
    std::sort(all_clients.begin(),all_clients.end());
    for (int i = 0;i < clients.size();++i)
    {
        std::cout << end_time[0] << end_time[1] << ":" << end_time[2] << end_time[3] << ' ' << 11 << ' ' << all_clients[i] << "\n";
    }
    return true;
}
std::string in_minutes_to_format(unsigned long long mins)
{
    int hours = mins / 60;
    int minutes = mins % 60;

    char buffer[6];  
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);

    return std::string(buffer);
}
int main(int argc, char* argv[]) {
   if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cout << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }
    std::vector<std::string>*cl =&clients;
    std::vector<std::string>*ql=&query_clients;
    std::vector<Table>*tl= &tables;
    std::string answers;
    std::vector<int> start_time;
    std::vector<int> end_time;
    bool checker;
    std::string error;
    unsigned long long razm = 0;
    unsigned long long price = 0;

    if (!check_int(razm,error,input) || razm == 0)
    {
        std::cout << error;
        return 1;
    }

    if (!set_time(start_time, error, input))
    {
        std::cout << error;
        return 1;
    }
    
    if (!set_time(end_time, error, input))
    {
        std::cout << error;
        return 1;
    }

    if (!check_int(price, error, input))
    {
        std::cout << error;
        return 1;
    }
    std::cout << start_time[0] << start_time[1] << ":" << start_time[2] << start_time[3] << "\n";
    if (!query(start_time, end_time, price, razm, input))
    {
        return 1;
    }
    input.close();
    std::cout << end_time[0] << end_time[1] << ":" << end_time[2] << end_time[3] << "\n";
    for (int i = 0;i < tables.size();++i)
    {
        if (!tables[i].is_active)
        {
            tables[i].time += (end_time[0] * 10 + end_time[1]) * 60 + (end_time[2] * 10 + end_time[3]) - tables[i].start_time;
            tables[i].money += (std::ceil(double((end_time[0] * 10 + end_time[1]) * 60 + (end_time[2] * 10 + end_time[3])-tables[i].start_time)/60)) * price;
        }
        std::cout << i + 1  << ' ' << tables[i].money << ' ' << in_minutes_to_format(tables[i].time);
        std::cout << "\n";
    }
}

