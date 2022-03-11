#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

void SaveIntToArr(int integer, int **Arr, int *SizeArr)
{
    (*SizeArr) = 0;
    if (integer != 0)
    {
        *SizeArr = 1;
        *Arr = (int *)malloc((size_t)(*SizeArr) * sizeof(int));
        int PlaceDesider = integer * -1, index = 0;

        //NAFIER nad NAF representation of integers scheme
        for (int i = 0; (integer - PlaceDesider) / 2 != 0; i++)
        {
            if (index + 1 >= (*SizeArr))
            {
                (*Arr) = (int *)realloc((*Arr), (size_t)(*SizeArr) * sizeof(int));
                (*SizeArr)++;
            }
            int temp = (integer - PlaceDesider) / 2;

            if (temp % 2 == 0)
                PlaceDesider = 0;
            else if (integer == INT_MIN || (temp - 1) % 4 == 0)
                PlaceDesider = 1;
            else if (integer == INT_MAX || (temp + 1) % 4 == 0)
                PlaceDesider = -1;

            if (PlaceDesider != 0) 
            {
                if (PlaceDesider == 1)
                    (*Arr)[index++] = (i * PlaceDesider);
                else
                {
                    if (i == 0)
                        (*Arr)[index++] = -1;
                    else
                        (*Arr)[index++] = i * PlaceDesider - 1;
                }
            }
            integer = temp;
        }
        if (PlaceDesider == 0)
            (*SizeArr) -= 2;
        else
            (*SizeArr)--;
    }
}
long long ArrToInt(int *Arr, int n)
{
    long long CurrentValue  = 0;

    //DivisionResultArruick exponentiation algorhythm
    for (int i = 0; i < n; i++)
    {
        int now = Arr[i], sign = 1;
        if (now < 0)
            sign = -1;
        long long exponentiation = 1, integer = 2, exponent = now;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
                exponentiation *= integer;

            integer *= integer;
            exponent /= 2;
        }
        CurrentValue  += (exponentiation * sign);
    }
    return CurrentValue;
}
int SmallerAbs(int FirstNumber, int SecondNumber, int *index1, int *index2){
    long diff = abs(FirstNumber) - abs(SecondNumber);
    if(!diff)
    {
        if(FirstNumber <= SecondNumber)
        {
            (*index1)++;
            return FirstNumber;
        }
        (*index2)++;
        return SecondNumber;
    }
    if(abs(FirstNumber) < abs(SecondNumber)){
        (*index1)++;
        return FirstNumber;
    }
    
    (*index2)++;
    return SecondNumber;
}
void SortWithNAFSchema(int **IntResultArr, int *SizeResultArr){
    int CountTrash = 0;

    //we sort the arr with NAF's Schema
    for (int i = 0; i < (*SizeResultArr) - 1; i++)
    {
        int FirstInt = (*IntResultArr)[i], SecondInt = (*IntResultArr)[i + 1];
        if ((SecondInt == FirstInt && i == 0 && CountTrash == 0) || (SecondInt == FirstInt && SecondInt != 0))
        {
            if (FirstInt >= 0)
            {
                (*IntResultArr)[i] = FirstInt + 1;
                (*IntResultArr)[i + 1] = 0;
                if (SecondInt != 0)
                    CountTrash++;
                i--;
            }
            else
            {
                (*IntResultArr)[i] = FirstInt - 1;
                (*IntResultArr)[i + 1] = 0;
                CountTrash++;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
        }
        else if (abs(FirstInt) > abs(SecondInt) && (SecondInt != 0 || (SecondInt == 0 && i == 0 && CountTrash == 0)))
        {
            (*IntResultArr)[i] = SecondInt;
            (*IntResultArr)[i + 1] = FirstInt;
            if (i > 0)
                i -= 2;
            else
                i--;
        }
        else if (((SecondInt + 1) * -1 == FirstInt && SecondInt != 0) || (FirstInt == 0 && SecondInt == 0 && CountTrash >= 2))
        {
            if (FirstInt == 0 && SecondInt == 0)
                CountTrash -= 2;
            if (FirstInt < 0)
            {
                (*IntResultArr)[i] = (FirstInt + 1) * -1;
                (*IntResultArr)[i + 1] = SecondInt - 1;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
            else if (i + 3 + CountTrash < (*SizeResultArr))
            {
                (*IntResultArr)[i] = (*IntResultArr)[i + 2 + CountTrash];
                (*IntResultArr)[i + 1] = (*IntResultArr)[i + 3 + CountTrash];
                (*IntResultArr)[i + 2 + CountTrash] = 0;
                (*IntResultArr)[i + 3 + CountTrash] = 0;
                if ((SecondInt + 1) * -1 == FirstInt)
                    CountTrash += 2;
                i--;
            }
            else if (i + 2 + CountTrash < (*SizeResultArr))
            {
                (*IntResultArr)[i] = (*IntResultArr)[i + 2 + CountTrash];
                (*IntResultArr)[i + 2 + CountTrash] = 0;
                (*IntResultArr)[i + 1] = 0;
                (*SizeResultArr)--;
            }
            else
                (*SizeResultArr) -= CountTrash;
            if (FirstInt == 0 && SecondInt == 0)
                CountTrash += 2;
        }
        else if (FirstInt == 0 && i != 0)
        {
            if (i + 2 + CountTrash < (*SizeResultArr))
            {
                (*IntResultArr)[i] = (*IntResultArr)[i + 1 + CountTrash];
                (*IntResultArr)[i + 1 + CountTrash] = (*IntResultArr)[i + 2 + CountTrash];
                (*IntResultArr)[i + 2 + CountTrash] = 0;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
            else if (i + 2 < (*SizeResultArr))
            {
                (*IntResultArr)[i] = (*IntResultArr)[i + 1];
                (*IntResultArr)[i + 1] = (*IntResultArr)[i + 2];
                (*IntResultArr)[i + 2] = 0;
                (*SizeResultArr)--;
                i--;
            }
            else
            {
                (*IntResultArr)[i] = (*IntResultArr)[i + 1];
                (*IntResultArr)[i + 1] = 0;
            }
        }
        else if (SecondInt == 0)
        {
            if (i + CountTrash + 1 < (*SizeResultArr))
            {
                (*IntResultArr)[i + 1] = (*IntResultArr)[i + CountTrash + 1];
                if ((*IntResultArr)[i + CountTrash + 1] != 0)
                    (*IntResultArr)[i + CountTrash + 1] = 0;
                i--;
            }
            else
                (*SizeResultArr)--;
        }
        else if (SecondInt == FirstInt * (-1))
        {
            if (SecondInt > FirstInt)
                (*IntResultArr)[i] = SecondInt - 1;
            else
                (*IntResultArr)[i] = FirstInt - 1;
            (*IntResultArr)[i + 1] = 0;
            CountTrash++;
            if (i > 0)
                i -= 2;
            else
                i--;
        }
        else if (FirstInt + 1 == SecondInt || FirstInt - 1 == SecondInt)
        {

            if (SecondInt >= 0)
            {
                (*IntResultArr)[i + 1] = SecondInt + 1;
                (*IntResultArr)[i] = SecondInt * -1;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
            else if (FirstInt < 0 && SecondInt < 0)
            {
                (*IntResultArr)[i + 1] = SecondInt - 1;
                (*IntResultArr)[i] = -1 - FirstInt;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
            else if (FirstInt >= 0 && SecondInt > 0)
            {
                (*IntResultArr)[i + 1] = SecondInt + 1;
                (*IntResultArr)[i] = FirstInt - 1;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
            else
            {
                (*IntResultArr)[i + 1] = SecondInt * -1;
                (*IntResultArr)[i] = FirstInt - 2;
                if (i > 0)
                    i -= 2;
                else
                    i--;
            }
        }
        else if ((-2 - FirstInt) == SecondInt)
        {
            (*IntResultArr)[i] = SecondInt + 1;
            (*IntResultArr)[i + 1] = 0;
            CountTrash++;
            if (i > 0)
                i -= 2;
            else
                i--;
        }
    }
}
void AddTwoArr(int *ArrInt1, int SizeArr1, int *ArrInt2, int SizeArr2, int **IntResultArr, int *SizeResultArr)
{
    if (SizeArr1 == 0 && SizeArr2 == 0)
    {
        *SizeResultArr = 0;
        return;
    }
    if (SizeArr2 == 0)
    {
        *IntResultArr = ArrInt1;
        (*SizeResultArr) = SizeArr1;
    }
    else if (SizeArr1 == 0)
    {
        *IntResultArr = ArrInt2;
        (*SizeResultArr) = SizeArr2;
    }
    else
    {
    	(*SizeResultArr) = 1;
        (*IntResultArr) = (int *)malloc((size_t)(*SizeResultArr) * sizeof(int));
        int iC = 0;

        for (int iA = 0, iB = 0; iA < SizeArr1 || iB < SizeArr2;)
        {
            if (iA + iB >= (*SizeResultArr))
            {
                (*SizeResultArr)++;
                (*IntResultArr) = (int *)realloc((*IntResultArr), (size_t)(*SizeResultArr) * sizeof(int));
            }

            if (iA == SizeArr1)
            {
                (*IntResultArr)[iC++] = ArrInt2[iB++];
            }
            else if (iB == SizeArr2)
            {
                (*IntResultArr)[iC++] = ArrInt1[iA++];
            }
            else
                (*IntResultArr)[iC++] = SmallerAbs(ArrInt1[iA], ArrInt2[iB], &iA, &iB);
        }
     
        SortWithNAFSchema(IntResultArr, SizeResultArr);

        int CountTrash = 0;
        for (int i = (*SizeResultArr) - 1; i >= 0; i--)
        {
            if ((*IntResultArr)[i] == 0 && i != 0)
                CountTrash++;
            else
                i = -1;
        }
        (*SizeResultArr) -= CountTrash;

        (*IntResultArr) = (int *)realloc((*IntResultArr), (size_t)(*SizeResultArr) * sizeof(int));
    }
}  
void ReverseArrValues(int *Arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (Arr[i] == 0)
            Arr[i] = -1;
        else if (Arr[i] == -1)
            Arr[i] = 0;
        else if (Arr[i])
            Arr[i] = (Arr[i] + 1) * -1;
    }
}
void SubtractionTwoArr(int *ArrInt1, int SizeArr1, int *ArrInt2, int SizeArr2, int **IntResultArr, int *SizeResultArr)
{
    ReverseArrValues(ArrInt2, SizeArr2); //insted of doing a - b we do a + (-b)
    AddTwoArr(ArrInt1, SizeArr1, ArrInt2, SizeArr2, IntResultArr, SizeResultArr);
    ReverseArrValues(ArrInt2, SizeArr2);
}
void MultiplicationTwoArr(int *ArrInt1, int SizeArr1, int *ArrInt2, int SizeArr2, int **IntResultArr, int *SizeResultArr)
{
    if (SizeArr1 > 0 && SizeArr2 > 0)
    {
        
        (*SizeResultArr) = 0;
        for (int iA = 0; iA < SizeArr1; iA++) // we gonna take one element of ArrInt1 and multiplication with all elements from Arr2Int
        {
            int *TempArr = NULL;
            int TempArrSize = SizeArr2, ElementArr1 = ArrInt1[iA];
            TempArr = (int *)realloc(TempArr, (size_t)TempArrSize * sizeof(int));

            for (int iB = 0; iB < SizeArr2; iB++)
            {
                int ElementArr1rr2 = ArrInt2[iB];
                if (ElementArr1 >= 0 && ElementArr1rr2 >= 0)
                    TempArr[iB] = ElementArr1 + ElementArr1rr2;
                else if (ElementArr1 < 0 && ElementArr1rr2 < 0)
                    TempArr[iB] = (-2) - ElementArr1 - ElementArr1rr2;
                else
                {
                    if (ElementArr1 == (ElementArr1rr2 * -1) || ElementArr1rr2 == (ElementArr1 * -1))
                    {
                        if (ElementArr1 < 0)
                            TempArr[iB] = ElementArr1 - ElementArr1rr2;
                        else
                            TempArr[iB] = ElementArr1rr2 - ElementArr1;
                    }
                    else if (ElementArr1 < ElementArr1rr2)
                        TempArr[iB] = ElementArr1 - ElementArr1rr2;
                    else
                        TempArr[iB] = ElementArr1rr2 - ElementArr1;
                }
            }

            int SizeCopyResultArr = (*SizeResultArr);
            int *CopyResultArr = NULL;
            CopyResultArr = (int *)realloc(CopyResultArr, (size_t)SizeCopyResultArr * sizeof(int));
            for (int ii = 0; ii < SizeCopyResultArr; ii++)
            {
                CopyResultArr[ii] = (*IntResultArr)[ii];
            }
            if ((*SizeResultArr) != 0)
            {
                free(*IntResultArr);
                (*SizeResultArr) = 0;
            }
            AddTwoArr(TempArr, TempArrSize, CopyResultArr, SizeCopyResultArr, IntResultArr, SizeResultArr); // like c+=c;
            if ((*IntResultArr) != TempArr)
                free(TempArr);
            if ((*IntResultArr) != CopyResultArr)
                free(CopyResultArr);
        }
    }
    else
    {
        (*IntResultArr) = (int *)realloc((*IntResultArr), sizeof(int));
        (*IntResultArr)[0] = 0;
        *SizeResultArr = 1;
    }
}
void ExponentiationArr1AndArr2(int *ArrInt1, int SizeArr1, int *ArrInt2, int SizeArr2, int **IntResultArr, int *SizeResultArr)
{
    int *p = NULL, *d = NULL, *remember_a = ArrInt1, remember_an = SizeArr1, *remember_b = NULL, remember_bn = SizeArr2, index = 0;
    remember_b = (int *)malloc((size_t)SizeArr2 * sizeof(int));

    for (int ii = 0; ii < SizeArr2; ii++) 
    {
        remember_b[ii] = ArrInt2[ii];
    }
    int *tempp = remember_b;
    (*SizeResultArr) = 1;
    (*IntResultArr) = (int *)malloc(sizeof(int));
    (*IntResultArr)[0] = 0;
    while (remember_bn > 0)
    {
        if (remember_b[0] == 0 || remember_b[0] == -1)
        {
            //c = c *a
            int *k = NULL, kn = 0;
            MultiplicationTwoArr(ArrInt1, SizeArr1, (*IntResultArr), (*SizeResultArr), &k, &kn);
            free(*IntResultArr);
            (*IntResultArr) = k;
            (*SizeResultArr) = kn;
            if (remember_bn == 1)
            {
            	free(d);
                ArrInt1 = remember_a;
                SizeArr1 = remember_an;
                free(tempp);
                return;
            }
        }

        //a = a * a;
        int TempArrSize = SizeArr1, dn = 0;
        p = (int *)malloc((size_t)TempArrSize * sizeof(int));
        d = NULL;
        for (int ii = 0; ii < TempArrSize; ii++)
        {
            p[ii] = ArrInt1[ii];
        }
        MultiplicationTwoArr(p, TempArrSize, ArrInt1, SizeArr1, &d, &dn);

        if (ArrInt1 != remember_a)
            free(ArrInt1);
        free(p);
        SizeArr1 = dn;
        ArrInt1 = d;

        int minus = 1;

        for (int i = 0; i < remember_bn; i++)
        {
            int integer = remember_b[i];
            if (i + 1 < remember_bn && integer == -1)
            {
                if (remember_b[i + 1] == 2)
                {
                    remember_b[i + 1] = 0;
                    remember_b++;
                    remember_bn--;
                }
                else
                {
                    integer = remember_b[i + 1];
                    i++;
                }
            }
            else if (i + 1 < remember_bn && integer == 0)
            {
                remember_b++;
                remember_bn--;
                index++;
                integer = remember_b[i];
            }
            if (integer < 0)
                remember_b[i] = integer + minus;
            else
                remember_b[i] = integer - minus;
        }
    }
    free(remember_b);
    ArrInt1 = remember_a;
    SizeArr1 = remember_an;
}
void ndivmod(int *ArrInt1, int SizeArr1, int *ArrInt2, int SizeArr2, int **DivisionResultArr, int *DivisionResultSize, int **RestArr, int *RestArrSize)
{
    // a : b    DivisionResultArr-division   r-rest
    int *remember_a = ArrInt1, remember_an = SizeArr1, *temp = NULL, temp_n = 0;
    bool r_done = false, answer_not_found_yet = true;
    (*DivisionResultSize) = 0, (*RestArrSize) = 0;

    int index = 0;
    while (ArrInt1[SizeArr1 - 1] >= 0 && SizeArr1 > 0 && answer_not_found_yet)
    {
        index++;
        SubtractionTwoArr(ArrInt1, SizeArr1, ArrInt2, SizeArr2, &temp, &temp_n);

        if (temp[temp_n - 1] < 0 && ArrToInt(temp, temp_n) <= 0)
        {
            answer_not_found_yet = false;
            if (temp_n == 2)
            {
                if (ArrToInt(temp, temp_n) == 0)
                {
                    (*RestArr) = (int *)malloc(sizeof(int));
                    (*RestArr)[0] = 0;
                    r_done = true;
                }
            }
            if (!r_done)
                index--;
        }
        else
        {
            if (ArrInt1 != remember_a)
                free(ArrInt1);
            SizeArr1 = temp_n;
            ArrInt1 = temp;
        }
    }

    SaveIntToArr(index, DivisionResultArr, DivisionResultSize);
    if (!r_done)
    {
        (*RestArr) = ArrInt1;
        (*RestArrSize) = SizeArr1;
    }
    ArrInt1 = remember_a;
    SizeArr1 = remember_an;
}