#include <iostream>
#include <string>
/*void choice()
{
    cout << "Vad vill du göra med IP't?" << endl;
    cout << "Skriv..." << endl;
    cout << "1 ; för att hitta klassen." << endl;
    cout << "2 ; för att konvertera till binärt." << endl;
    cout << "3 ; för att få NetID." << endl;
    cout << "4 ; för att få 'Brodcast' adressen" << endl;
    cout << "5 ; för att "

}*/

int convertToIntegerList(std::string ip)
{
    int ipList[4];
    int nOfByte = -1;
    std::string byte = "";
    for (char& c : ip)
    {
        if (c != '.')
        {
            byte.push_back(c);
            //std::cout << c << std::endl;
        }
        else
        {
            nOfByte += 1;
            ipList[nOfByte] = stoi(byte);
            std::cout << ipList[nOfByte] << std::endl;
            byte = "";
        }
    }
    nOfByte += 1;
    ipList[nOfByte] = stoi(byte);
    std::cout << ipList[nOfByte] << std::endl;
    std::cout << ipList << std::endl;
    return 0;
}

std::string submitIp()
{
    std::string ip;
    std::cout << "Ange en ip adress: " << std::endl;
    std::cin >> ip;
    return ip;
}


int main()
{
    convertToIntegerList(submitIp());
    system("pause");
    return 0;
}