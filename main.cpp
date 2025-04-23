#include <cstdio>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <map>
#include "PatternTemplates.h"
#include <list>
using namespace std;

enum class OrganizationBelonging : int
{
    State = 1, //Государственная
    Private = 2, //Частная

    Undefined = 0
};



using namespace std;
class Person{
public:
    string Name;
    int Age;
    int Experience;
    Person(string name, int age, int experience):
        Name(name), Age(age), Experience(experience){}

    Person();

    bool Equals(Person client2)
    {
        if (this->Age == client2.Age && this->Experience == client2.Experience &&
            this->Name == client2.Name)
                return true;
        else return false;
    }


};
class FinancialAndCreditOrganization{ //Финансово-кредитные организации
public:
    FinancialAndCreditOrganization(Person client, string name,
                                   double account, double price, OrganizationBelonging type):
        Client(client), Name(name), Account(account), SharePrice(price), Belong(type){};
    virtual string GetMoney(Person person, double count){} //methods
    virtual string GetJob(Person person){}
    virtual string SetMoney(Person person, double count){}
    double GetSharePrice(){
        return SharePrice;
    }
    bool IsGoodOrganization(){
        if(Belong == OrganizationBelonging::State && SharePrice >= 250)
            return true;
        else return false;
    }
    OrganizationBelonging GetBelong()
    {
        return Belong;
    }
    void CloseAccont()
    {
        Account = 0;
    }
    void AddAccont()
    {
        Account = 100;
    }
    void AddAccont(Person client)
    {
        Client = client;
        Account = 100;
    }
    Person Client; //fields
    string Name;
    double Account;
protected:
    OrganizationBelonging Belong;
private:
    double SharePrice;

};
class Bank : public FinancialAndCreditOrganization
{
public:
    Bank(const Person& client, string name,
         double account, string cardNumber,
         OrganizationBelonging type, double price):
            CardNumber(cardNumber),
            Client(client),
            FinancialAndCreditOrganization(client, name, account, price, type){}
    Bank(const Person& client) :
        Client(client), FinancialAndCreditOrganization(client, "Some Bank", 0, 50, OrganizationBelonging::Undefined){}
    Bank(const Person& client, OrganizationBelonging type, double price) :
        Client(client),
        FinancialAndCreditOrganization(client, "Some Bank", 0, price, type){}
    string Name;
    OrganizationBelonging Belong;
    string GetMoney(Person person, double count) override
    {
        Account -= count;
        if (count > Account)
        {
            return person.Name + " снимает со счёта " + to_string(count) + ". В кредит: " + to_string(abs(Account));
        }
        return person.Name + " снимает со счёта " + to_string(count);
    }
    string SetMoney(Person person, double count) override
    {
        Account += count;
        return "Баланс " + person.Name + " пополнен на " + to_string(count) + ". Номер карты: " + CardNumber;
    }
    string GetJob(Person person) override
    {
        if (person.Age >= 18 and person.Experience >= 2)
        {
            return person.Name + " Принят на работу";
        }
        return person.Name + " Не принят на работу";
    }

private:
    Person Client; //fields
    double Account;
    string CardNumber;

};
class PensionFund : public FinancialAndCreditOrganization
{
public:
    PensionFund(const Person& client, string name,
                double account, string snilsNumber,
                OrganizationBelonging type, double price):
                    SnilsNumber(snilsNumber),
                    Client(client),
                    FinancialAndCreditOrganization(client, name, account, price, type){}
    PensionFund(const Person& client) :
        Client(client),
        FinancialAndCreditOrganization(client, "Some Pension Fund", 0, 70, OrganizationBelonging::Undefined){}
    PensionFund(const Person& client, OrganizationBelonging type, double price) :
        Belong(type), Client(client),
        FinancialAndCreditOrganization(client, "Some Pension Fund", 0, price, type){}
    string Name;
    OrganizationBelonging Belong;
    string GetMoney(Person person, double count) override
    {
        if (count > Account)
        {
            return "На счете " + person.Name + " недостаточно денег для снятия "  + to_string(count);
        }
        Account -= count;
        return person.Name + " снимает со счёта " + to_string(count);
    }
    string SetMoney(Person person, double count) override
    {
        setlocale(LC_ALL,"RUSSIAN");
        Account += count;
        return "Баланс " + person.Name + " пополнен на " + to_string(count) + ". Номер СНИЛС: " + SnilsNumber;
    }
    string GetJob(Person person) override
    {
        if (person.Age >= 22 and person.Experience >= 6)
        {
            return person.Name + " Принят на работу";
        }
        return person.Name + " Не принят на работу";
    }

private:
    Person Client; //fields
    double Account;
    string SnilsNumber;

};
class InsuranceCompany : public FinancialAndCreditOrganization
{
public:
    InsuranceCompany(const Person& client,
                     string name, double account,
                     string osagoNumber, OrganizationBelonging type, double price):
        OsagoNumber(osagoNumber), Client(client),
        FinancialAndCreditOrganization(client, name, account, price, type){}
    InsuranceCompany(const Person& client) :
        Client(client),
        FinancialAndCreditOrganization(client, "Some Insurance Company", 0, 100, OrganizationBelonging::Undefined){}
    InsuranceCompany(const Person& client, OrganizationBelonging type, double price) :
        Client(client),
        FinancialAndCreditOrganization(client, "Some Insurance Company", 0, price, type){}
    map<string, double> payments = {
        {"Рука", 10000}, {"Нога", 20000}, {"Челюсть", 100000}
    };
    string Name;
    OrganizationBelonging Belong;
    string GetPayment(Person person, string cause)
    {
        auto pay = payments.find(cause);
        if (pay != payments.end()) {
            return person.Name + " получает выплату за " + cause + " в размере: " + to_string(pay->second);
        } else {
            return "Нет выплат по указанной причине";
        }
    }
    string GetMoney(Person person, double count) override
    {
        if (count > Account)
        {
            return "На счете недостаточно денег для снятия " + to_string(count);
        }
        Account -= count;
        return person.Name + " снимает со счёта " + to_string(count);
    }
    string SetMoney(Person person, double count) override
    {
        setlocale(LC_ALL,"RUSSIAN");
        Account += count;
        return "Баланс " + person.Name + " пополнен на " + to_string(count) + ". Номер страхования: " + OsagoNumber;
    }
    string GetJob(Person person) override
    {
        if (person.Age >= 18 and person.Experience >= 5)
        {
            return person.Name + " Принят на работу";
        }
        return person.Name + " Не принят на работу";
    }
private:
    Person Client; //fields
    double Account;
    string OsagoNumber;

};

enum class ActionsWithAccount : int
{
  AddMoney = 1,
  GetMoney = 2,
  CloseAccount = 3,


  AddAccount = 4,

  None = 0
};
//стратегия
class AccountStrategy
{
public:
  virtual ~AccountStrategy() {}
  virtual void ActionWithAccount(FinancialAndCreditOrganization org, Person client) = 0;
};

class AddMoneyStrategy : public AccountStrategy
{
  void ActionWithAccount(FinancialAndCreditOrganization org, Person client)
  {
      if (org.Client.Equals(client))
        {
            //cout << org.SetMoney(client, 100);
            cout << client.Name + " пополняет счет на 100р" << endl;
        }
      else cout << "Клиент не найден. Откройте счет" << endl;
  }

};

class GetMoneyStrategy : public AccountStrategy
{
  void ActionWithAccount(FinancialAndCreditOrganization org, Person client)
  {
      if (org.Client.Equals(client))
        {
            //cout << org.GetMoney(client, 100);
            cout << client.Name + " снимает со счета 100р" << endl;
        }
      else cout << "Клиент не найден. Откройте счет" << endl;
  }
};

class AddAccount : public AccountStrategy
{
  void ActionWithAccount(FinancialAndCreditOrganization org, Person client)
  {
      if (org.Client.Equals(client))
        {
            org.AddAccont();
            cout << "счет " + client.Name + " открыт. 100р в подарок за открытие." << endl;
        }
      else{
            org.AddAccont(client);
            cout << "Клиент не найден. Откройте счет" << endl;
      }
  }
};

class CloseAccount : public AccountStrategy
{
  void ActionWithAccount(FinancialAndCreditOrganization org, Person client)
  {
      if (org.Client.Equals(client))
        {
            org.CloseAccont();
            cout << "счет " + client.Name + " закрыт" << endl;
        }
      else cout << "Клиент не найден. Откройте счет" << endl;
  }
};

// Фабричный метод для создания стратегий
AccountStrategy *CreateAccountStrategy(ActionsWithAccount actions)
{
  switch(actions)
  {
    case ActionsWithAccount::AddMoney: return new AddMoneyStrategy;
    case ActionsWithAccount::GetMoney: return new GetMoneyStrategy;
    case ActionsWithAccount::AddAccount: return new AddAccount;

    // Новый способ (для варианта 2)
    case ActionsWithAccount::CloseAccount: return new CloseAccount;

    default: return nullptr;
  }
}


enum class FinancialAndCreditOrganizationType : int
{
    Bank = 1,
    PensionFund = 2,
    InsuranceCompany = 3,

    Undefined = 0 // На всякий случай
};

FinancialAndCreditOrganization *CreateOrganization(FinancialAndCreditOrganizationType type, Person client, OrganizationBelonging belong, double price)
{
    FinancialAndCreditOrganization *newOrganization = nullptr;

    if(type == FinancialAndCreditOrganizationType::Bank)
    {
        newOrganization = new Bank(client, belong, price);
    }
    else if(type == FinancialAndCreditOrganizationType::PensionFund)
    {
        newOrganization = new PensionFund(client, belong, price);
    }
    else if(type == FinancialAndCreditOrganizationType::InsuranceCompany)
    {
        newOrganization = new InsuranceCompany(client, belong, price);
    }

    return newOrganization;
}

void GetOneRuble(Iterator<FinancialAndCreditOrganization*> *it, Person client)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        FinancialAndCreditOrganization *currentOrganization = it->GetCurrent();
        currentOrganization->GetMoney(client, 1);
        cout << "Mike снял со счета " << currentOrganization->Name << " 1 рубль"<< endl;
    }

}

// Декоратор итератора для выделения организаций по принадлежности

class OrganizationBelongingDecorator : public IteratorDecorator<class FinancialAndCreditOrganization*>
{
private:
    OrganizationBelonging TargetBelong;

public:
    OrganizationBelongingDecorator(Iterator<FinancialAndCreditOrganization*> *it, OrganizationBelonging belong)
    : IteratorDecorator<FinancialAndCreditOrganization*>(it), TargetBelong(belong) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetBelong() != TargetBelong)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetBelong() != TargetBelong);
    }
};

// Декоратор итератора для выделения хороших или плохих организаций
class OrganizationGoodDecorator : public IteratorDecorator<class FinancialAndCreditOrganization*>
{
private:
    bool TargetGood;

public:
    OrganizationGoodDecorator(Iterator<FinancialAndCreditOrganization*> *it, bool isGood)
    : IteratorDecorator<FinancialAndCreditOrganization*>(it), TargetGood(isGood) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->IsGoodOrganization() != TargetGood){
            It->Next();
        }
    }
    void Next()
    {
        do{
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->IsGoodOrganization() != TargetGood);
    }
};

// Декоратор итератора для выделения организаций со стоимостью акций менее (зн.) и более (зн.)
class OrganizationPriceDecorator : public IteratorDecorator<class FinancialAndCreditOrganization*>
{
private:
    double TargetPrice;

public:
    OrganizationPriceDecorator(Iterator<FinancialAndCreditOrganization*> *it, double price)
    : IteratorDecorator<FinancialAndCreditOrganization*>(it), TargetPrice(price) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetSharePrice() >= TargetPrice){
            It->Next();
        }
    }
    void Next()
    {
        do{
            It->Next();
        } while(!It->IsDone() && It->GetCurrent()->GetSharePrice() >= TargetPrice);
    }
};

int main()
{
    setlocale(LC_ALL,"RUSSIAN");
    Person mike{"Mike", 18, 2};
    Bank sber{mike, "Sberbank", 0, "22220000", OrganizationBelonging::State, 250};
    cout << "Bank: " << endl;
    cout << sber.GetJob(mike) << endl;
    cout << sber.SetMoney(mike, 1000) << endl;
    cout << sber.GetMoney(mike, 2000) << endl;
    InsuranceCompany alfa{mike, "alfaStrahovanie", 0, "1298466", OrganizationBelonging::Private, 170};
    cout << "\nInsurance: " << endl;
    cout << alfa.GetJob(mike) << endl;
    cout << alfa.SetMoney(mike, 1000) << endl;
    cout << alfa.GetMoney(mike, 2000) << endl;
    cout << alfa.GetPayment(mike, "Рука") << endl;
    PensionFund pfr{mike, "PensionFundRF", 0, "2387566589", OrganizationBelonging::State, 310};
    cout << "\nPensionFund: " << endl;
    cout << pfr.GetJob(mike) << endl;
    cout << pfr.SetMoney(mike, 1000) << endl;
    cout << pfr.GetMoney(mike, 2000) << endl;

    size_t N = 0;
    cout << "Введите количество организаций: ";
    cin >> N;

    cout << endl;
    Queue<FinancialAndCreditOrganization*> OrganizationQueue;
    for(size_t i=0; i<N; i++)
    {
        int organiztion_num = rand()%3+1; // Число от 1 до 3 (случайная организация)
        int organiztion_belong = rand()%2+1; //частная или гос.
        int organiztion_share_price = rand()%500+1;
        OrganizationBelonging organization_belonging = static_cast<OrganizationBelonging>(organiztion_belong);
        FinancialAndCreditOrganizationType organization_type = static_cast<FinancialAndCreditOrganizationType>(organiztion_num);
        FinancialAndCreditOrganization *newOrganization = CreateOrganization(organization_type, mike, organization_belonging, organiztion_share_price);
        OrganizationQueue.Enqueue(newOrganization);
    }
    cout << "Размер очереди организаций: " << OrganizationQueue.Size() << endl;

    list<FinancialAndCreditOrganization*> OrganizationVectorDefault; // а еще можно vector, forward_list, ...
    for(size_t i=0; i<N; i++)
    {
        int organiztion_num = rand()%3+1; // Число от 1 до 3 (случайная организация)
        int organiztion_belong = rand()%2+1; //частная или гос.
        int organiztion_share_price = rand()%500+1;
        OrganizationBelonging organization_belonging = static_cast<OrganizationBelonging>(organiztion_belong);
        FinancialAndCreditOrganizationType organization_type = static_cast<FinancialAndCreditOrganizationType>(organiztion_num);
        FinancialAndCreditOrganization *newOrganization = CreateOrganization(organization_type, mike, organization_belonging, organiztion_share_price);
        OrganizationVectorDefault.push_back(newOrganization); // Добавить новый фрукт в конец списка
    }

    cout << endl << "Get one ruble all using iterator:" << endl;
    Iterator<FinancialAndCreditOrganization*> *it3 = OrganizationQueue.GetIterator();
    GetOneRuble(it3, mike);
    delete it3;
    cout << endl;
    CustomVector<FinancialAndCreditOrganization*> OrganizationVector;
    for(size_t i=0; i<N; i++)
    {
        int organiztion_num = rand()%3+1; // Число от 1 до 3 (случайная организация)
        int organiztion_belong = rand()%2+1; //частная или гос.
        int organiztion_share_price = rand()%500+1;
        OrganizationBelonging organization_belonging = static_cast<OrganizationBelonging>(organiztion_belong);
        FinancialAndCreditOrganizationType organization_type = static_cast<FinancialAndCreditOrganizationType>(organiztion_num);
        FinancialAndCreditOrganization *newOrganization = CreateOrganization(organization_type, mike, organization_belonging, organiztion_share_price);
        OrganizationVector.Append(newOrganization);
    }
    cout << "Размер вектора организаций: " << OrganizationQueue.Size() << endl;

    // Обход всех элементов вектора при помощи итератора
    cout << endl << "Get one ruble all using iterator:" << endl;
    Iterator<FinancialAndCreditOrganization*> *it4 = OrganizationVector.GetIterator();
    GetOneRuble(it4, mike);
    delete it4;
    cout << endl;

    // Обход всех государственных организаций
    cout << endl << "Get one ruble all state using iterator:" << endl;
    Iterator<FinancialAndCreditOrganization*> *goodIt = new OrganizationBelongingDecorator(OrganizationQueue.GetIterator(), OrganizationBelonging::State);
    GetOneRuble(goodIt, mike);
    delete goodIt;

    // Обход всех организаций с ценой на акции выше 200р
    cout << endl << "Get one ruble all higher than 200 price using iterator:" << endl;
    Iterator<FinancialAndCreditOrganization*> *expensiveIt = new OrganizationPriceDecorator(OrganizationQueue.GetIterator(), 200);
    GetOneRuble(expensiveIt, mike);
    delete expensiveIt;

    // Обход всех хороших (гос. + цена акций выше 150р) организаций
    cout << endl << "Get one ruble all good using iterator:" << endl;
    Iterator<FinancialAndCreditOrganization*> *wellIt = new OrganizationGoodDecorator(OrganizationQueue.GetIterator(), true);
    GetOneRuble(wellIt, mike);
    delete wellIt;

    // Демонстрация работы адаптера
    cout << endl << "Get one ruble all private higher than 300 using adapted iterator (another container):" << endl;
    Iterator<FinancialAndCreditOrganization*> *adaptedIt =
        new ConstIteratorAdapter<std::list<FinancialAndCreditOrganization*>,FinancialAndCreditOrganization*>(&OrganizationVectorDefault);
    Iterator<FinancialAndCreditOrganization*> *adaptedPrivateIt =
    new OrganizationPriceDecorator(new OrganizationBelongingDecorator(adaptedIt, OrganizationBelonging::Private), 300);
    GetOneRuble(adaptedPrivateIt, mike);
    delete adaptedPrivateIt;

    cout << endl << endl << "Демонстрация работы стратегии" << endl;
    //Демонстрация работы стратегии
    for(int i=0; i<10; i++)
    {
        int action_num = rand()%4+1; // Число от 1 до 4 (случайная организация)
        ActionsWithAccount action = static_cast<ActionsWithAccount>(action_num);
        AccountStrategy *acc_strat = CreateAccountStrategy(action);
        acc_strat->ActionWithAccount(sber, mike);
    }

    return 0;
}
