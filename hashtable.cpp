#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<iostream>
#include<string>
#include<sstream>
#include<math.h>

using namespace std;

unsigned int table_sz;

typedef enum op_t
{
	OP_TYPE_GET = 0,
	OP_TYPE_PUT = 1
} op_t;

bool isPrime(unsigned int f)
{
	int count = 0;
	if(f == 2 || f == 3)
		return true;

	if(f % 2 == 0  || f % 3  == 0)
		return false;

	for(int j = 4; j < f; j++)
	{
		if(f % j == 0)
		{
			count++;
			break;
		}
	}
	if(count == 0)
		return true;
	return false;
}

unsigned int findNextPrime(unsigned int f)
{
	if(isPrime(f))
		return f;

	while(!isPrime(++f))
	{
	}
	return f;
}
		
unsigned int compute_ht_size(unsigned int song_length)
{
	unsigned int table_sz = findNextPrime(song_length);
	return table_sz;
}

unsigned int stringToInt(string s, unsigned int start_pos)
{
	unsigned int result,i = 0, str_length;

	str_length = s.length();
	
	/* Extract 4 characters and place them in to integer */
	while(((start_pos + i) < str_length) && (i < 4))
	{
	   result << 8;
	   result |= (s[start_pos + i]);
	   i++;
	}
	
	/* If end of string, compensate by filling 0s */
	if(i < 4)
	{
	   result = result << ((4-i) * 8);
	}

	return(result);
}

long* split_chunk(string s,int chunk_size,int num_chunks)
{
	int strLength = s.length(), j = 0, n;
	
	string *chunks = new string[num_chunks];

	for(int i = 0 ; i < strLength; i += chunk_size)
	{
		if (i + chunk_size > strLength)
		{
			chunks[j] =  s.substr(i,(strLength  - i));
			int k = chunk_size - chunks[j].length();
			while(k--)
				chunks[j].push_back(0);
			j++;
		}
		else
		    chunks[j++] =  s.substr(i,chunk_size);
	}

	long *blocks = (long *)new long[num_chunks];
	
	for(int i = 0 ; i < num_chunks; i ++)
	{
		cout << chunks[i] << endl;
	    blocks[i] = std::stol(string_to_hex(chunks[i]),nullptr,16);
		cout << blocks[i] <<endl;
	}

	if(chunks)
	{
		delete[] chunks;
	}
	return blocks;
}

unsigned int reverseBits(unsigned int num)
{
	unsigned int count = sizeof(num) * 8 - 1;
	unsigned int reverse_num = num;
	
	num >>= 1; 
	while(num)
	{
	reverse_num <<= 1;	 
	reverse_num |= num & 1;
	num >>= 1;
	count--;
	}
	reverse_num <<= count;
	return reverse_num;
}

unsigned long xor_fold(long *blocks,int n)
{
	unsigned long result = 0;

	for(int i = 0; i < n; i++)
	{
		result ^= blocks[i];
	}
	return result;
}

int hash_key(string s)
{
	int strLength = s.length(), n;
	if(strLength%4  == 0)
	    n = (strLength/4);
	else
		n = (strLength/4)+1;

	long *chunks= split_chunk(s,4,n);
	
	for(int i = 0; i < n ;i += 2)
	{
		chunks[i] = reverseBits(chunks[i]);
		cout << chunks[i] << "\n";
	}

	unsigned long result = xor_fold(chunks,n);

	if(chunks)
	{
		delete[] chunks;
	}
	return result % table_sz;
}

unsigned int randomFold(unsigned int num, unsigned int bit_chunk_len)
{
	unsigned int result = 0;
	unsigned int mask = 0;
	
	if(bit_chunk_len>=32)
	{
		/* Large number, return incoming number*/
		return num;
	}
	else
	{
		/*Generate mask for bit chunk*/
		mask = (1 << bit_chunk_len) - 1;
		
		/* Repeat for all chunks */
		while(num)
		{
			/* Ex-OR the extracted chunks*/
			result = result ^ (num & mask);
			/* Prepare for next chunk*/
			num = num >> bit_chunk_len;
		}
	}
	
	return result;
}

op_t findRandomOpType(unsigned int table_size)
{
	int randon_num;
	op_t result_op = OP_TYPE_GET;
	unsigned int fold;
	
	fold = ceil(log((double)table_sz)));
	randon_num = (int)rand();

	/* Find MSB of random folded result */
	if(randomFold((unsigned int)randon_num,fold) & (1 << (fold-1)))
	{
		result_op = OP_TYPE_PUT;
		printf("PUT");
	}
	else
	{
	    result_op = OP_TYPE_GET;
		printf("GET");
	}
	return result_op;
}

int main()
{
	time_t t;
	op_t random_operation_type;

	/* Intialize random number generator */
    srand((unsigned int) time(&t));

	/* Determine List Length after parsing the input */
	list_length = 8;
	
	table_sz = compute_ht_size(list_length);
	/* Find the random operation type */

	random_operation_type = findRandomOpType(table_sz);

	printf("%d\n",hash_key("Listen to the music"));
	
	
	return 0;
}