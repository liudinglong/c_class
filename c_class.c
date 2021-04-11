#include <stdio.h>
#include<stdlib.h>
//C 语言没有类，但可以用结构体充当一个类
//与类不同，结构体只能定义变量，不能够定义函数，可以通过函数指针的方法来实现其功能 
//定义“类 ”的成员变量以及方法,这里实现了类的封装
typedef struct Person{
    char* name;
    int age;
    void (*IntroduceFunc)(struct Person this);
}Person; 

//定义函数功能 
void IntroduceFunc(struct Person this){
    printf("my name is %s, I am %d years old.\n", this.name, this.age);
} 

//定义“类 ”的构造函数
//与面向对象不同，C语言的“类”的 构造函数不能放在“类”中，只能放在“类”外
//构造函数主要完成 变量的初始化，以及函数指针的赋值 
Person *NewPerson(char* name1, int age1){
    Person* this = (Person *)malloc(sizeof(Person));
    this->name = name1;
    this->age = age1;
    this->IntroduceFunc = IntroduceFunc;
    return this;
} 

void DestoryPerson(Person* p){
    free(p);
    p = NULL;
}
//这里实现了类似C++的继承
typedef struct Programmer{
    Person person;
    char* language;
} Programmer;

void ProgrammerIntroduct(struct Programmer this){
    printf("my name is %s, I am %d years old. I am a programmer", this.person.name, this.person.age);
}

//子类Programmer的构造函数
Programmer* NewProgrammer(char *name1, int age1, char* language1){
    Programmer* this = (Programmer *)malloc(sizeof(Programmer));
    this->language = language1;
    this->person = *NewPerson(name1, age1);
    this->person.IntroduceFunc = ProgrammerIntroduct;
    return this;
}

void DestoryProgrammer(Programmer* p){
    DestoryPerson(&(p->person));
    free(p);
    p=NULL;
}

//主函数调用 
int main(){
    Person *person = NewPerson("liudinglong", 18);
    person->IntroduceFunc(*person);
    Programmer* pro = NewProgrammer("programmer1", 21, "C++");
    Person *person2 = (Person *)pro;
    person2->IntroduceFunc(*person2);
    return 0;
} 
