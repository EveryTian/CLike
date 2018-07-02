int foo (int x, int y){
    int res = 0;

    
    return res;
}

void foo2(int n){
    int tmp = 1;
    
    tmp = foo(n, foo(1,2));
}

int main (void){
    int m = 1;
    int n = 2;

    m = m * n;
    foo2(m);
    return 0;
}	

