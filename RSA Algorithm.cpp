#include<bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/lexical_cast.hpp>
using namespace boost::multiprecision;
using namespace std;

int prime_bit,k=30;
cpp_int N, Z, d, e, P;
string sentMessage,receivedMessage,sentMessageToNumber;

cpp_int power(cpp_int b,cpp_int e,cpp_int m)
{
    cpp_int a=1;

    while(e>0)
    {
        if(e%2==1)
        {
            a=(a*b)%m;
        }

        b=pow(b,2)%m;
        e=e/2;
    }

    return a%m;
}

bool checkIfPrime(cpp_int n)
{
    if(n==1)
    {
        return false;
    }

    for (int i=0; i<k; i++)
    {
        cpp_int x= rand()%(n-1)+1;
        if(power(x,n-1,n)!=1)
        {
            return false;
        }
    }
    return true;
}

void generatePrimeNumber()
{
    cpp_int p,q;
    cpp_int min = pow((cpp_int)2,prime_bit-1);
    cpp_int max = pow((cpp_int)2,prime_bit)-1;

    srand(time(0));
    while(1)
    {
        p = min+(rand()%(max-min+1));
        if(checkIfPrime(p))
            break;
    }
    srand(time(0)+1);
    while(1)
    {
        q = min+(rand()%(max-min+1));
        if(checkIfPrime(q))
            break;
    }

    N=p*q;
    Z=(p-1)*(q-1);

    cout<<"\nPrime numbers: "<<p<<" and "<<q<<endl;

}

void textToNumber()
{
    for(int i=0; i<sentMessage.length(); i++)
    {
        int value = (int)sentMessage[i];
        sentMessageToNumber+=to_string(value);
    }

    P=(cpp_int)sentMessageToNumber;
    cout<<"\nPlain text to number format: "<<sentMessageToNumber<<endl;

}

void numberToText(cpp_int p)
{
    cpp_int num=0;
    char ch;

    string s=boost::lexical_cast<string>(p);

    for(int i=0; i<s.length(); i++)
    {
        num=num*10+(s[i]-48);

        if (num>=32 && num<=126)
        {
            ch=char(num);
            receivedMessage+=ch;
            num=0;
        }
    }

    cout<<"\nOriginal message is (Verification): "<<receivedMessage<<endl;
}

cpp_int GCD(cpp_int a,cpp_int b)
{
    cpp_int min=a,max=b;

    if(a>b)
    {
        min = b;
        max = a;
    }

    return (max%min==0)?min:GCD(max%min,min);
}

cpp_int calculateD()
{
    for(cpp_int i=2; i<Z; i++)
    {
        if(GCD(i,Z)==1)
        {
            return i;
        }
    }
}

cpp_int calculateE(cpp_int a,cpp_int m)
{
    a=a%m;
    for(cpp_int x=1; x<m; x++)
    {
        if ((a*x)%m==1)
            return x;
    }
}

int main()
{
    cout<<"\nEnter number of bit for prime number generation: ";
    cin>>prime_bit;

    generatePrimeNumber();

    d=calculateD();
    e=calculateE(d,Z);

    cout<<"\nPublic key: ("<<N<<","<<e<<")"<<endl;
    cout<<"\nPrivate key: ("<<d<<","<<e<<")"<<endl;

    cout<<"\nEnter your message to encrypt using private key: ";
    cin.ignore();
    getline(cin,sentMessage);

    textToNumber();

    cpp_int C=pow(P,(int)e)%N;

    cout<<"\nCiphertext: "<<C<<endl;

    cpp_int p = pow(C,(int)d)%N;

    cout<<"\nPlain text in number format after decryption: "<<p<<endl;

    numberToText(p);

    return 0;
}
