
int square(int n){
	return n*n;
}

int doub(int n){
	return 2*n;
}

int triple(int n){
	return 3*n;
}

int fact(int n){
	if(n==0) return 1;
	int fact=1;
	for(int i=1; i<=n; ++i)
		fact *= i;
	return fact;
}

int fib(int n){
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	int f0=0, f1=1;
	for(int i=2; i<=n; ++i){
		int temp = f0;
		f0 = f1;
		f1 += temp;
	}
	return f1;
}

int sumOfDigits(int n){
	int digit,sum=0;
    while (n > 0)
    {
        digit = n % 10;
        sum  = sum + digit;
        n /= 10;
    }

    return sum;
}

int decToBin(int n){
	int bin=0,rem,base=1;
	while (n > 0){
		rem = n % 2;
		bin = bin + rem * base;
		n = n / 2;
		base = base * 10;
	}
	return bin;
}

int binToDec(int n){
	int dec=0,rem,base=1;
	while (n > 0){
		rem = n % 10;
		dec = dec + rem * base;
		n = n / 10 ;
		base = base * 2;
    }
    return dec;
}