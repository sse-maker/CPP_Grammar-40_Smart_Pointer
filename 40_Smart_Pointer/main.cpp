//
//  main.cpp
//  40_Smart_Pointer
//
//  Created by 세광 on 2021/07/30.
//

// 스마트 포인터: 사용이 끝난 메모리를 자동으로 해제
// unique_ptr, shared_ptr, weak_ptr

#include <iostream>
#include <memory>

using namespace std;

class Test {
public:
    Test(int x) : x(x) { cout << "생성자" << endl; }
    ~Test() { cout << "소멸자" << endl; }
    int GetX() const { return x; }
    
private:
    int x;
};

int main() {
    // unique 포인터의 특성: 문법적으로 한 대상은 한 unique 포인터만 가리킬 수 있음
    // unique 포인터에 다른 포인터를 대입하는 것은 불가능
    unique_ptr<Test> a(new Test(5));
    cout << a->GetX() << endl;
    cout << "====" << endl;
    a.reset(new Test(6)); // 다른 객체를 가리키도록 재설정, 원래 객체는 소멸
    cout << a->GetX() << endl;
    cout << "====" << endl;
    unique_ptr<Test> b(a.release()); // 소유권 이전 (a가 가리키는 메모리에 대한 소유권을 포기하고 다른 포인터로 넘겨주겠다는 의미)
    
    // shared 포인터: 여러 포인터가 한 객체 공유 가능 (unique 포인터와 반대)
    shared_ptr<Test> c(new Test(7));
    {
        shared_ptr<Test> d = c;
        cout << c.use_count() << endl;
        cout << d.use_count() << endl;
    }
    cout << c.use_count() << endl;
    
    // weak 포인터의 특성: 소유권은 없지만 어떤 객체를 가리킬 수 있음 (shared 포인터가 가리키고 있는 다른 대상을 가리킬 때 사용, use_count()에 관여 X)
    weak_ptr<Test> e;
    {
        shared_ptr<Test> f(new Test(8));
        e = f;
        cout << f.use_count() << endl;
        cout << e.use_count() << endl;
        if(!e.expired()) { // b가 가리키고 있는 객체가 살아 있다면
            cout << e.lock()->GetX() << endl; // lock()을 통해 그 객체에 대한 shared 포인터를 가져올 수 있음
        }
    }
    cout << e.use_count() << endl;
    if(!e.expired()) {
        cout << e.lock()->GetX() << endl;
    }
}
