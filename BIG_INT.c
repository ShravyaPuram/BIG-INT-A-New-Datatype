#include<stdio.h>
#include<string.h>
#define SIZE 310
typedef struct BigInt_tag
{
    int A[SIZE];
    int size;
    int sign;
} BigInt;
BigInt ADD(BigInt ,BigInt );


void input(BigInt *nptr)
{
    char str[SIZE];
    printf("Enter the number:\n");
    scanf("%s",str);
    int length=strlen(str);
    int ind=0;
    if(str[0]=='-')
    {
        nptr->sign=-1;       //-1 -ve
        int j=1;
        while(str[j]=='0')
        {
            j++;
        }
        for(int i=length-1;i>=j;i--)
        {
               nptr->A[ind]=str[i]-'0';
               ind++; 
        }
    }
    else
    {
        nptr->sign=1;       //1 +ve
        int j=0;
        while(str[j]=='0')
        {
            j++;
        }
        for(int i=length-1;i>=0;i--)
        {
               nptr->A[ind]=str[i]-'0';
               ind++; 
        }
    }
    nptr->size=ind;
}


void display_BigInt(BigInt n)
{
    int i=n.size-1;
    if(n.sign==-1)
    {
        printf("-");
    }
    while(n.A[i]==0 && n.size!=1)
    {
        n.size--;
        i--;
    }
    for(int i=(n.size)-1;i>=0;i--)
    {
        printf("%d",n.A[i]);
    }
    printf("\n");
}



int compare(BigInt n1, BigInt n2) {
    if (n1.sign != n2.sign) {
        // If signs are different, return based on signs
        if(n1.sign==1)
        {
            return 1;     
        }
        else return -1;
    }

    if (n1.size != n2.size) {
        // If sizes are different, return based on sizes
        if(n1.size > n2.size && n1.sign==1)
        {
            return 1;
        }
        else if(n1.size>n2.size && n1.sign==-1)
        {
            return -1;
        }
        else if(n1.size<n2.size && n1.sign==1)
        {
            return -1;
        }
        else return 1;
    }

    // Compare A elements from most significant digit to least significant digit
    if(n1.sign==-1 && n2.sign==-1)
    {
    for (int i = n1.size - 1; i >= 0; i--) {
        if (n1.A[i] != n2.A[i]) {
            if(n1.A[i] > n2.A[i])
            {
                return -1;
            }
            else 
            {
                return 1;
            }
        }
    }
    }
    else
    {
    for (int i = n1.size - 1; i >= 0; i--) {
        if (n1.A[i] != n2.A[i]) {
            if(n1.A[i] > n2.A[i])
            {
                return 1;
            }
            else 
            {
                return -1;
            }
        }
    }
    }

    // numbers are equal
    return 0;
}



BigInt SUB(BigInt n1, BigInt n2) {
    BigInt result;
    int cmp = compare(n1, n2);
    //printf("%d\n",cmp);
    if (cmp == 0) {
        // numbers are equal, return zero
        //printf("Check");
        result.size = 1;
        result.A[0] = 0;
        result.sign = 1;
        return result;
    }

    if (n1.sign != n2.sign) {
        // Signs are different, perform ADD with proper sign
        if (n1.sign == -1) {
            n2.sign = -1;
            result = ADD(n1, n2);
        } else {
            n2.sign = 1;
            result = ADD(n1, n2);
            //result.sign = -1;
        }
        return result;
        //display_BigInt(result);
    }

    // Signs are the same, perform subraction
    if (cmp < 0) {
        // Swap n1 and n2 if n1 < n2
        if(n1.sign==1 && n2.sign==1){
        BigInt temp = n1;
        n1 = n2;
        n2 = temp;
        }
        result.sign = -1;
        //printf("Check\n");
    } else {
        result.sign = 1;
        if(n1.sign==-1 && n2.sign==-1){
        BigInt temp = n1;
        n1 = n2;
        n2 = temp;
        }
    }
    int i;
    for (i = 0; i < n2.size; i++) {
        int diff = n1.A[i] -n2.A[i];
        if (diff < 0) {
            diff += 10;
            n1.A[i+1]--;
        } 
        result.A[i] = diff;
    }    
    while(i<n1.size)
    {
        if(n1.A[i]<0)
        {
            n1.A[i]+=10;
            n1.A[i+1]--;
        }
        result.A[i]=n1.A[i];
        i++;
    }
    result.size = n1.size;
    return result;
}


BigInt ADD(BigInt n1, BigInt n2) {
    BigInt result;
    // Handle signs
    if (n1.sign == -1 && n2.sign == -1) {
        result.sign = -1;
    } else if (n1.sign == 1 && n2.sign == -1) {
        n2.sign = 1;
        return SUB(n1, n2);
    } else if (n1.sign == -1 && n2.sign == 1) {
        n1.sign = 1;
        return SUB(n2, n1);
    } else {
        result.sign = 1;
    }
    int i,sum,carry=0;
    for(i=0;i<n1.size && i<n2.size;i++)
    {
        sum=n1.A[i]+n2.A[i]+carry;
        carry=sum/10;
        result.A[i]=sum%10;
    }
    while(i<n1.size)
    {
        sum=n1.A[i]+carry;
        carry=sum/10;
        result.A[i]=sum%10;
        i++;
    }
    while(i<n2.size)
    {
        sum=n2.A[i]+carry;
        carry=sum/10;
        result.A[i]=sum%10;
        i++;
    }
    if(carry>0)
    {
        result.A[i]=carry;
        i++;
    }
    result.size=i;
    return result;
}


BigInt MULTI(BigInt n1, BigInt n2) {
    BigInt result;
    int sum,i,j,carry=0;
    //Initialize result A
    for(i=0;i<SIZE;i++)
    {
        result.A[i]=0;
    }
    for(int i=0;i<n1.size;i++)
    {
        for(j=0;j<n2.size;j++)
        {
            result.A[i+j]+=n1.A[i]*n2.A[j];
            result.A[i+j+1]+=result.A[i+j]/10;
            result.A[i+j]%=10;
        }
    }
    // Find the actual size of the result
    int size = SIZE;
    while (size > 1 && result.A[size - 1] == 0)
        size--;

    result.size = size;
    // Determine the sign of the result
    if( result.size==1 && result.A[0]==0){
        result.sign=1;
    }
    else{
    result.sign = n1.sign * n2.sign;
    }

    return result;
    
}


int main()
{
    BigInt a,b,add,sub,multi;
    input(&a);
    input(&b);
    add=ADD(a,b);
    //printf("%d\n",add.size);
    sub=SUB(a,b);
    multi=MULTI(a,b);
    printf("The addition of these is:\n");
    display_BigInt(add);
    printf("The Subraction of these is:\n");
    display_BigInt(sub);
    printf("The multiplication of these is:\n");
    display_BigInt(multi);
    return 0;
}