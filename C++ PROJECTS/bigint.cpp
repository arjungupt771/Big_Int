#include<iostream>
#include<vector>
#include<string>
#include<algorithm>


class BigInt{

    private:
    std::vector<int>digits;
    bool isNegative;

    public:

    BigInt() : isNegative(false){}
    BigInt(const std:: string &num);

    //utility functions
    void removeLeadingZeros();
    BigInt add(const BigInt &other) const;
    BigInt subtract(const BigInt &other) const;
    BigInt karatsubaMultiply(const BigInt &other) const;
    BigInt multiply(const BigInt &other) const;
    BigInt modulo(const BigInt &other) const;
    BigInt power(const BigInt &exp, const BigInt &mod) const;
    BigInt divison(const BigInt &other) const;
    BigInt comparison(const BigInt &other) const;


    //comparison operators
    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;


    //overload operators

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator%(const BigInt &other) const;
    BigInt operator^(const BigInt &other) const;
    BigInt operator/(const BigInt &other) const;

    void print() const;

    private:
     std::pair<BigInt, BigInt> divideAndRemainder(const BigInt &other) const;

};

//constructor
BigInt :: BigInt(const std::string &num){
    isNegative = (num[0] == '-');
    for(int i=num.length()-1; i>=(isNegative ? 1:0);--i){
        digits.push_back(num[i]-'0');
    }
}


//utility function to remove leading zeros
void BigInt :: removeLeadingZeros(){
    while(digits.size()>1 && digits.back()==0){
        digits.pop_back();
    }
    if(digits.size()==1 && digits[0]==0){
        isNegative ; false;
    }
}

//addition
BigInt BigInt ::add(const BigInt &other)const{
    if(isNegative!=other.isNegative){
        if(isNegative){
            return other.add(*this);
        } else{
            return add(other);
        }
    }

    BigInt result;
    result.isNegative = isNegative;
    int carry=0;
    size_t maxSize = std::max(digits.size(),other.digits.size());
    result.digits.resize(maxSize);

    for(size_t i=0;maxSize || carry;++i){
        if(i<digits.size()) carry+=digits[i];
        if(i<other.digits.size()) carry+=other.digits[i];
        result.digits[i]=carry%10;
        carry/=10;
    }
    if(carry){
        result.digits.push_back(carry);
    }

    return result;

}


//Subtract

BigInt BigInt::subtract(const BigInt &other) const{
    BigInt result;
    result.isNegative = isNegative;

    int borrow=0;
    result.digits.resize(digits.size());

    for(size_t i=0;i<digits.size();++i){
        int diff=digits[i] - borrow - (i< other.digits.size() ? other.digits[i] :0);
        borrow = (diff<0);
        if(borrow) diff +=10;
        result.digits[i] = diff;
    }

    result.removeLeadingZeros();
    return result;
}

//Karatsuba multiplication function
BigInt BigInt::karatsubaMultiply(const BigInt &other) const{
    size_t n=std::max(digits.size(), other.digits.size());
    if(n<=32){
        return multiply(other);
    }

    n=(n/2) + (n%2);
    BigInt low1, high1, low2, high2;
    low1.digits = std::vector<int>(digits.begin(), digits.begin() + std::min(n, digits.size()));
    high1.digits = std::vector<int>(digits.begin() + std::min(n, digits.size()), digits.end());

    low2.digits = std::vector<int>(other.digits.begin(), other.digits.begin() + std::min(n, other.digits.size()));
    high2.digits = std::vector<int>(other.digits.begin() + std::min(n, other.digits.size()), other.digits.end());

    BigInt z0 = low1.karatsubaMultiply(low2);
    BigInt z1 = (low1.add(high1)).karatsubaMultiply(low2.add(high2));
    BigInt z2 = high1.karatsubaMultiply(high2);

    BigInt result;
    result.digits.resize(z0.digits.size() + 2*n);
    for(size_t i=0; i<z0.digits.size(); ++i) result.digits[i] += z0.digits[i];
    for(size_t i=0; i<z1.digits.size();++i) result.digits[i+n] +=z1.digits[i];
    for(size_t i=0;i<z2.digits.size();++i) result.digits[i+ 2*n] += z2.digits[i];

    result.removeLeadingZeros();
    return result;
}

BigInt BigInt::multiply(const BigInt &other) const{
    BigInt result;
    result.digits.resize(digits.size() + other.digits.size());

    for(size_t i=0;i<digits.size();++i){
        int carry=0;
        for(size_t j=0;j<other.digits.size() || carry;++j){
            int64_t curr = result.digits[i+j] + digits[i]*(j<other.digits.size() ? other.digits[j] :0) + carry;
            result.digits[i+j] = curr%10;
            carry = curr/10;
        }
    }

    result.removeLeadingZeros();
    return result;
}

//helper function for division
std :: pair<BigInt, BigInt> BigInt::divideAndRemainder(const BigInt &other)const{
    BigInt dividend = *this;
    BigInt divisor = other;
    BigInt quotient("0");
    BigInt remainder = dividend;

    if(divisor == BigInt("0")){
        throw std::runtime_error("Divison by zero");
    }

    if(dividend < divisor){
        return {BigInt("0"), dividend};
    }

    size_t shift = dividend.digits.size() - divisor.digits.size();
    divisor.digits.insert(divisor.digits.begin(), shift, 0);

    for(size_t i=0;i<=shift; ++i){
        int q=0;
        while(remainder >= divisor){
            remainder = remainder.subtract(divisor);
            q++;
        }
        quotient.digits.insert(quotient.digits.begin(),q);
        divisor.digits.erase(divisor.digits.begin());
    }
    quotient.removeLeadingZeros();
    remainder.removeLeadingZeros();
    return {quotient, remainder};
}

//divison operator
BigInt BigInt::divison(const BigInt &other) const{
    return divideAndRemainder(other).first;
}

//modulo operator
BigInt BigInt::modulo(const BigInt &other)const{
    return divideAndRemainder(other).second;
}

// power using divide and conquer
BigInt BigInt::power(const BigInt &exp, const BigInt &mod)const{
    if(exp == BigInt("0")) return BigInt("1");
    BigInt half = power(exp / BigInt("2"), mod);
    BigInt halfMod = (half*half)%mod;
    if(exp.digits[0]%2==0){
        return halfMod;
    }
    else{
        return (halfMod * (*this)) % mod;
    }
}

//comparison operators

bool BigInt::operator==(const BigInt &other)const{
    return digits == other.digits && isNegative == other.isNegative;
}

bool BigInt::operator!=(const BigInt &other)const{
    return !(*this == other);
}

bool BigInt::operator<(const BigInt &other) const{
    if(isNegative !=other.isNegative){
        return isNegative;
    }
    if(digits.size() !=other.digits.size()){
        return isNegative ? digits.size() > other.digits.size():digits.size() < other.digits.size();
    }
    for(int i=digits.size() - 1;i>=0;--i){
        if(digits[i] != other.digits[i]){
            return isNegative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
    }
    return false;
}

bool BigInt::operator<=(const BigInt &other) const{
    return *this < other || *this == other;
}

bool BigInt::operator>(const BigInt &other)const{
    return !(*this <= other);
}

bool BigInt::operator>=(const BigInt &other)const{
    return !(*this < other);
}

//overloaded
BigInt BigInt::operator+(const BigInt &other)const{
    return add(other);
}

BigInt BigInt::operator-(const BigInt &other)const{
    return subtract(other);
}

BigInt BigInt::operator*(const BigInt &other)const{
    return karatsubaMultiply(other);
}

BigInt BigInt::operator/(const BigInt &other)const{
    return divison(other);
}

BigInt BigInt::operator%(const BigInt &other)const{
    return modulo(other);
}

void BigInt::print() const{
    if(isNegative) std::cout<<"-";
    for(auto it = digits.rbegin(); it !=digits.rend();++it){
        std::cout<<*it;
    }
    std::cout<<std::endl;
}

int main(){
    std::string num1,num2;
    std::cout<<"Enter two large numbers:"<<std::endl;
    std::cin>>num1>>num2;

    BigInt bigInt1(num1);
    BigInt bigInt2(num2);

    BigInt product = bigInt1 * bigInt2;
    BigInt quotient = bigInt1/bigInt2;
    BigInt remainder = bigInt1 % bigInt2;
    BigInt modExpResult = bigInt1.power(bigInt2, BigInt("1000000007"));

    std::cout<<"Product: ";
    product.print();

    std::cout<<"Quotient:";
    quotient.print();

    std::cout<<"Remainder:";
    remainder.print();

    std::cout<<"Modular Exponentiation Result:";
    modExpResult.print();

    return 0;


}
