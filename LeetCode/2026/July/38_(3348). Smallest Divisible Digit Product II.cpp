// LC 3348. Smallest Divisible Digit Product II
// Digits 1-9 only carry prime factors {2,3,5,7}. Factor t into these;
// any leftover prime -> impossible ("-1").
// Pack required powers of 2/3 into digits 8,9,6 (fewest digits possible);
// 5's and 7's each need exactly that many literal '5'/'7' digits.
// Then: keep num's prefix as long as possible, bump one digit up,
// pad with '1's, append the minimal digits (ascending) at the end.

struct PC { long long a=0,b=0,c=0,d=0; }; // powers of 2,3,5,7

class Solution {
public:
    PC dig[10]; // prime-power contribution of each digit 0-9

    Solution(){
        dig[2]={1,0,0,0}; dig[3]={0,1,0,0}; dig[4]={2,0,0,0};
        dig[5]={0,0,1,0}; dig[6]={1,1,0,0}; dig[7]={0,0,0,1};
        dig[8]={3,0,0,0}; dig[9]={0,2,0,0};
        // dig[0], dig[1] stay {0,0,0,0}
    }

    PC sub(const PC&x, const PC&y){ // clamped subtraction (x-y, floor 0)
        return { max(0LL,x.a-y.a), max(0LL,x.b-y.b), max(0LL,x.c-y.c), max(0LL,x.d-y.d) };
    }

    bool covers(const PC&need, const PC&have){
        return have.a>=need.a && have.b>=need.b && have.c>=need.c && have.d>=need.d;
    }

    // minimal digit multiset (counts for digits 2-9) covering `need`
    array<long long,10> minDigits(const PC& need){
        array<long long,10> f{};
        long long c8 = need.a/3, r2 = need.a%3;
        long long c9 = need.b/2, c3 = need.b%2;
        long long c4 = r2/2, c2 = r2%2, c6 = 0;
        if(c2==1 && c3==1){ c2=0; c3=0; c6=1; }        // merge 2+3 -> 6 (fewer digits)
        if(c3==1 && c4==1){ c2=1; c6=1; c3=0; c4=0; }  // 4+3 -> 6+2 (smaller arrangement)
        f[2]=c2; f[3]=c3; f[4]=c4; f[5]=need.c;
        f[6]=c6; f[7]=need.d; f[8]=c8; f[9]=c9;
        return f;
    }

    long long total(const array<long long,10>& f){
        long long s=0; for(int i=2;i<=9;i++) s+=f[i]; return s;
    }

    string build(const array<long long,10>& f){ // ascending digits = smallest arrangement
        string r;
        for(int d=2; d<=9; d++) r += string(f[d], char('0'+d));
        return r;
    }

    string smallestNumber(string num, long long t) {
        PC need; // required prime powers
        while(t%2==0){ t/=2; need.a++; }
        while(t%3==0){ t/=3; need.b++; }
        while(t%5==0){ t/=5; need.c++; }
        while(t%7==0){ t/=7; need.d++; }
        if(t!=1) return "-1"; // leftover prime factor: impossible

        auto minF = minDigits(need);
        long long minLen = total(minF);
        int n = num.size();

        // even the shortest valid number is longer than num -> it's automatically the answer
        if(minLen > n) return build(minF);

        PC prefix; // running prime-power total of num[0..n-1], peeled from the back
        for(char ch : num) prefix = { prefix.a+dig[ch-'0'].a, prefix.b+dig[ch-'0'].b,
                                       prefix.c+dig[ch-'0'].c, prefix.d+dig[ch-'0'].d };

        int firstZero = -1;
        for(int i=0;i<n;i++) if(num[i]=='0'){ firstZero=i; break; }

        if(firstZero==-1){
            firstZero = n;
            if(covers(need, prefix)) return num; // num itself already works
        }

        // try to keep prefix num[0..i-1], raise digit i, fill the rest optimally
        for(int i=n-1;i>=0;i--){
            int d = num[i]-'0';
            prefix = sub(prefix, dig[d]); // now = prime-power total of num[0..i-1]
            int spaceAfter = n-1-i;
            if(i > firstZero) continue; // prefix would contain a zero digit -> invalid

            for(int bd=d+1; bd<=9; bd++){
                PC rem = sub(sub(need, prefix), dig[bd]);
                auto f = minDigits(rem);
                long long need2 = total(f);
                if(need2 <= spaceAfter){
                    long long ones = spaceAfter - need2;
                    return num.substr(0,i) + char('0'+bd) + string(ones,'1') + build(f);
                }
            }
        }

        // no answer of length n -> smallest zero-free (n+1)-digit number works (guaranteed, since minLen<=n)
        auto f = minDigits(need);
        long long ones = (long long)(n+1) - total(f);
        return string(ones,'1') + build(f);
    }
};
