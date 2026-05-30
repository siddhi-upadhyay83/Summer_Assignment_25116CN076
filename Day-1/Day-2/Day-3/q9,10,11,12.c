// 9 check whether the number is prime //
#include <stdio.h>
int main()
{
  int n, i, prime = 1;
  printf("enter the number\n");
  scanf("%d", &n);
  for (i = 2; i <= n / 2; i++){
    if (n % i == 0) {
      prime = 0;
      break;
    }
  }
  if (prime == 1) {
    printf("%d is prime", n);
  }else {
    printf("%d is not prime ", n);
  }
  return 0;
}

//10.find prime number in range//
#include <stdio.h>
#include <math.h>
int isPrime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
int main() {
    int low, high, count = 0;
    printf("Enter lower number\n ");
    scanf("%d", &low);
    printf("Enter upper number\n ");
    scanf("%d", &high);
    printf("\nPrime numbers between %d and %d:\n", low, high);
    for (int i = low; i <= high; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n\nTotal primes found: %d\n", count);
    return 0;
}


//11.find gcd of two number//
#include<stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {
    int a, b;
    printf("Enter two numbers\n ");
    scanf("%d %d", &a, &b);
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    printf("GCD of %d and %d = %d\n", a, b, gcd(a, b));
    return 0;
}

//12.find LCM of two number//
#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}
int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    printf("LCM of %d and %d = %d\n", a, b, lcm(a, b));
    return 0;
}
  