#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
using namespace std;

const int N = 4;
void print_matrix(int(*a)[N])
{
	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)
			cout << "+---";
		cout << "+\n|";
		for (int j = 0; j < N; j++)
			cout << setw(3) << a[i][j] << "|";
	}
	cout << endl;
	for (int j = 0; j < N; j++)
		cout << "+---";
	cout << "+";
}
vector<pair<int, int>> vct;

void _stdcall push_coord(int i, int j)
{
	vct.push_back(pair<int, int>(i, j));
}

int main()
{
	//task 1
	{
		int a[N][N] =
		{
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 }
		};
		/*
		int a[N][N] =
		{
			{  1, 12,  3,  8 },
			{  5,  6,  7,  4 },
			{  9, 16, 11, 14 },
			{ 13, 15,  2, 10 }
		};*/
		/*
		int a[N][N] =
		{
			{ 1, 12 },
			{ 5,  6 },
		};
		int a[N][N] =
		{
			{ 1 }
		};*/
		int i, j;
		cout << "\nSource matrix:";
		print_matrix(a);
		_asm
		{
			cmp N, 1
			je trivial_case
			lea ebx, a

			//Local max-s
			mov i, 0
			loop_i :
				mov j, 0
				loop_j :

					mov edi, i
					imul edi, N
					mov esi, j
					add esi, edi
					mov edx, [ebx+esi*4]

					mov ecx, N
					dec ecx

					i_dec :
					cmp i, 0
					je i_inc
					mov edi, i
					dec edi
					imul edi, N
					mov esi, j
					add esi, edi
					mov eax, [ebx+esi*4]
					cmp edx, eax
					jl not_max

					i_inc :
					cmp i, ecx
					je j_dec
					mov edi, i
					inc edi
					imul edi, N
					mov esi, j
					add esi, edi
					mov eax, [ebx+esi*4]
					cmp edx, eax
					jl not_max

					j_dec :
					cmp j, 0
					je j_inc
					mov edi, i
					imul edi, N
					mov esi, j
					dec esi
					add esi, edi
					mov eax, [ebx+esi*4]
					cmp edx, eax
					jl not_max

					j_inc :
					cmp j, ecx
					je comparison_end
					mov edi, i
					imul edi, N
					mov esi, j
					inc esi
					add esi, edi
					mov eax, [ebx+esi*4]
					cmp edx, eax
					jl not_max
					
					comparison_end :

					push j
					push i
					call push_coord

					not_max :

				inc j
				mov eax, N
				cmp j, eax
				jl loop_j

			inc i
			mov eax, N
			cmp i, eax
			jl loop_i

			//Row Elements Sorting
			mov i, 0
			loop2_i :
				mov ecx, N
				dec ecx

				loop2_j :
				mov j, 0
				sort_loop :
					mov edi, i
					imul edi, N
					mov esi, j
					add esi, edi
					imul esi, 4
					mov eax, [ebx+esi]
					mov edx, [ebx+esi+4]
					cmp eax, edx
					jg swap_el
					cont_sort:
					inc j
					cmp j, ecx
					jl sort_loop
				dec ecx
				jnz loop2_j

			inc i
			mov eax, N
			cmp i, eax
			jl loop2_i
			
			jmp sort_end
			swap_el :
				mov [ebx+esi], edx
				mov [ebx+esi+4], eax
				jmp cont_sort

			sort_end :

			//Rows Sorting
				
			mov ecx, N
			dec ecx
			loop3_i :
			mov i, 0
			r_sort_loop :
				mov edi, i
				imul edi, N
				mov eax, N
				dec eax
				add edi, eax
				mov esi, edi
				add esi, N
				mov eax, [ebx+edi*4]
				mov edx, [ebx+esi*4]
				push ecx
				cmp eax, edx
				jg swap_row
				cont_r_sort:
				pop ecx
				inc i
				cmp i, ecx
				jl r_sort_loop
			dec ecx
			jnz loop3_i

			
			jmp r_sort_end
			swap_row :
				mov edi, i
				imul edi, N
				mov esi, edi
				add esi, N
				mov ecx, N
				swap_loop :
					mov eax, [ebx+edi*4]
					mov edx, [ebx+esi*4]
					mov [ebx+edi*4], edx
					mov [ebx+esi*4], eax
					inc esi
					inc edi
				loop swap_loop
				jmp cont_r_sort

			trivial_case :
				push 0
				push 0
				call push_coord
			r_sort_end :



		}

		cout << "\n\nLocal maximums:\n";
		for (pair<int, int> p : vct)
			cout << "(" << p.first << "," << p.second << "), ";

		cout << "\n\nResult matrix:";
		print_matrix(a);
		_getch();
	}

	//task 2
	{
		int i, j, max_row, max_col, max_row_count, max_col_count;
/*
		const int M = 4, N = 4;
		int a[M][N] =
		{
			{ 1, 0, 1, 1 },
			{ 1, 1, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 0 }
		};

		const int M = 4, N = 4;
		int a[M][N] =
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 }
		};

		const int M = 1, N = 1;
		int a[M][N] =
		{
			{ 1 }
		};
*/
		const int M = 3, N = 8;
		int a[M][N] =
		{
			{ 0, 0, 0, 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 1, 1, 1, 1, 0 },
			{ 0, 1, 1, 1, 0, 1, 1, 1 }
		};

		_asm
		{
			//Row max
			
			mov edx, 0
			mov max_row, 0
			mov max_row_count, 0
			mov i, 0
			loop_row_i :
				mov j, 0
				loop_row_j :

					mov edi, i
					imul edi, N
					add edi, j
					cmp a[edi*4], 0
					je reset_row_count
					inc edx
					mov eax, N
					dec eax
					cmp j, eax
					jl no_res_r
					reset_row_count :
						cmp edx, max_row_count
						jle continue_row
						mov max_row_count, edx
						mov eax, i
						mov max_row, eax

					continue_row :
					mov edx, 0
					no_res_r :

				inc j
				mov eax, N
				cmp j, eax
				jl loop_row_j
			inc i
			mov eax, M
			cmp i, eax
			jl loop_row_i


			//Col max

			mov edx, 0
			mov max_col, 0
			mov max_col_count, 0
			mov j, 0
			loop_col_j :
				mov i, 0
				loop_col_i :

					mov edi, i
					imul edi, N
					add edi, j
					cmp a[edi*4], 0
					je reset_col_count
					inc edx
					mov eax, M
					dec eax
					cmp i, eax
					jl no_res_c
					reset_col_count :
						cmp edx, max_col_count
						jle continue_col
						mov max_col_count, edx
						mov eax, j
						mov max_col, eax

					continue_col :
					mov edx, 0
					no_res_c :

				inc i
				mov eax, M
				cmp i, eax
				jl loop_col_i
			inc j
			mov eax, N
			cmp j, eax
			jl loop_col_j

		}
		cout << "\n\nMax row: " << max_row << " with " << max_row_count;
		cout << "\nMax col: " << max_col << " with " << max_col_count;
		_getch();
	}
	//task 3
	{
		int i, j, max_row, max_col, max_row_count, max_col_count, shift;

		const int M = 4, N = 24, N_red = N/8;
		unsigned char a[M][N_red] =
		{
			{0b01010001, 0b11001001, 0b11001001 },
			{0b00010010, 0b01000010, 0b11001001 },
			{0b01001111, 0b11000101, 0b11001001 },
			{0b10111011, 0b11101111, 0b11001001 }
		};

/*
		const int M = 7, N = 32, N_red = N/8;
		unsigned char a[M][N_red] =
		{
			{ 0b00001000, 0b00000000, 0b00000000, 0b00000000 },
			{ 0b11111110, 0b11000110, 0b11101110, 0b11000110 },
			{ 0b00000000, 0b11000110, 0b11000000, 0b11001100 },
			{ 0b11110000, 0b11000010, 0b11000000, 0b00111000 },
			{ 0b11000000, 0b00000110, 0b10000000, 0b11001100 },
			{ 0b11001111, 0b11110010, 0b01111100, 0b11000110 },
			{ 0b00000000, 0b00000010, 0b00000000, 0b01000000 }
		};
*/
		_asm
		{
			//Row max
			
			mov edx, 0
			mov max_row, 0
			mov max_row_count, 0
			mov i, 0
			loop_b_row_i :
				mov j, 0
				mov shift, 128
				loop_b_row_j :
					mov edi, i
					imul edi, N_red
					push edx
					mov eax, j
					mov edx, eax
					and edx, 7
					shr eax, 3
					add edi, eax
					pop edx
					mov al, byte ptr shift
					test byte ptr a[edi], al
					jz reset_b_row_count
					inc edx
					mov eax, N
					dec eax
					cmp j, eax
					jl no_b_res_r
					reset_b_row_count :
						cmp edx, max_row_count
						jle continue_b_row
						mov max_row_count, edx
						mov eax, i
						mov max_row, eax

					continue_b_row :
					mov edx, 0
					no_b_res_r :
					shr shift, 1
					cmp shift, 0
					jg dont_reset_shift_r
					mov shift, 128
					dont_reset_shift_r :

				inc j
				mov eax, N
				cmp j, eax
				jl loop_b_row_j
			inc i
			mov eax, M
			cmp i, eax
			jl loop_b_row_i


			//Col max
			
			mov edx, 0
			mov max_col, 0
			mov max_col_count, 0
			mov shift, 128
			mov j, 0
			loop_b_col_j :
				mov i, 0
				loop_b_col_i :
					mov edi, i
					imul edi, N_red
					push edx
					mov eax, j
					mov ebx, 8
					cdq
					idiv ebx
					add edi, eax
					pop edx
					mov al, byte ptr shift
					test byte ptr a[edi], al
					jz reset_b_col_count
					inc edx
					mov eax, M
					dec eax
					cmp i, eax
					jl no_b_res_c
					reset_b_col_count :
						cmp edx, max_col_count
						jle continue_b_col
						mov max_col_count, edx
						mov eax, j
						mov max_col, eax

					continue_b_col :
					mov edx, 0
					no_b_res_c :

				inc i
				mov eax, M
				cmp i, eax
				jl loop_b_col_i

				shr shift, 1
				cmp shift, 0
				jg dont_reset_shift_c
				mov shift, 128
				dont_reset_shift_c :

			inc j
			mov eax, N
			cmp j, eax
			jl loop_b_col_j

		}
		cout << "\n\nMax row: " << max_row << " with " << max_row_count;
		cout << "\nMax col: " << max_col << " with " << max_col_count;

		_getch();
	}
}