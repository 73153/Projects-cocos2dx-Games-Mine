//
//  main.cpp
//  testCPlus
//
//  Created by Vivek on 01/10/12.
//  Copyright (c) 2012 user15. All rights reserved.
//

#include <iostream>

int Afunc(int,int);
int Bfunc(int,int);
int Cfunc(int,int);
int Dfunc(int,int);

int v1;
int v2;
int v3;



class A
{

public:
   public:int Afunc(int x,int y)
    {
       
        return v1+v2;
    }
};

class B:public A{

    public:int Bfunc(int a,int b )
    {
        return v1*v2;
    }
};


class C:public B,public A {
   public:int Cfunc(int s,int f)
    {
        return v1/v2;
    }
};

class D:public C,public B,public A
{

    public:int Dfunc(int w,int i)
    {
        return v1-v2;
    }
};

int main(int argc, const char * argv[])
{

    std::cout << "Hello, World!\n";
    
    
    
    std::cout << "Enter two numbers:" << std::endl;
    std::cin>>v1;
    std::cin>>v2;
    A a;
    B b;
    C c;
    D d;
    int res1;
    int res2;
    int res3;
    int res4;
    res1=a.Afunc(v1,v2);
     res2=b.Bfunc(v1,v2);
     res3=c.Cfunc(v1,v2);
     res4=d.Dfunc(v1,v2);
    
   
    std::cout << "The Addition of " << v1 << " and " << v2<< " is " << res1<< std::endl;
    std::cout << "The multiplication of " << v1 << " and " << v2<< " is " << res2<< std::endl;
    std::cout << "The division of " << v1 << " and " << v2<< " is " << res3<< std::endl;
    std::cout << "The subtraction of " << v1 << " and " << v2<< " is " << res4<< std::endl;

    

            
}
