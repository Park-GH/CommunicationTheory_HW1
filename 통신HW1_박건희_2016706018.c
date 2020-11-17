//2016706018 박건희
//header
#include <stdio.h>

//matched filter function
void rect_filter(char file_name[20], int opt, int sample_nun, int bit_num);		//input 1 2 3의 matched filter인 적분기함수
void tri_filter(char file_name[20], int opt, int bit_num);							//input 4의 matched filter 함수


//main function
int main() {
	rect_filter("input#1.dat", 0, 10, 1000);	//input#1.dat 기준값0, 비트당 샘플수 10, 비트 수 1000
	rect_filter("input#2.dat", 100, 10, 1000);	//input#2.dat 기준값100, 비트당 샘플수 10, 비트 수 1000
	rect_filter("input#3.dat", 0, 20, 500);		//input#3.dat 기준값0, 비트당 샘플수 20, 비트 수 500
	rect_filter("input#4.dat", 0, 10, 1000);	//input#4.dat 기준값0, 비트당 샘플수 10, 비트 수 1000
	tri_filter("input#4.dat", 0, 1000);			//input#4.dat 기준값0, 비트 수 1000 (최적의 필터)
}



/*
적분기 함수
precondition으로 파일이름, 적분시 판정값, 비트당 sample 갯수, 비트 수를 인자로 받는다.
*/
void rect_filter(char file_name[20],int opt, int sample_num, int bit_num) {
	FILE* fin, *fbit;						//파일구조체의 포인터 선언
	fopen_s(&fin, file_name, "rt");			//fin에 file_name 인자에 들어가는 파일 txt 형태로 읽기
	fopen_s(&fbit, "bit.dat", "rt");		//fbit에 bit.dat 파일 txt 형태로 읽기
	float input[20] = { 0.0, };				// 파형 배열, sample 갯수 10개 또는 20개인 점을 고려해서 20개로 선언
	float sum = 0;							// 적분값
	int detect;								// 적분값이 기준치보다 크냐 작냐로 판정된 bit
	int bit;								// bit.dat에 저장된 실제 bit
	int i, k;								// 반복문용 
	float error_count = 0;					// 에러 bit 갯수

	for (i = 0; i < bit_num; i++) {			//bit갯수 만큼 반복
		for (k = 0; k < sample_num; k++) {	//bit당 sample수만큼 반복
			fscanf_s(fin, "%f", &input[k]);	//bit의 sample을 input배열에 순서대로 저장
			sum += input[k];				//sample을 적분
		}									//for문 종료시 sum에 bit 하나의 sample 적분값 저장
		if (sum > opt)						//적분값이 기준보다 크면 1, 작으면 0
			detect = 1;
		else if (sum < opt)
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//실제 bit 읽어들임
		if (detect != bit)					//만약 판정된 bit와 실제 bit가 다르면 
			error_count++;					//에러 갯수 추가

		sum = 0;							//적분값 0 초기화
	}
	//모든 bit의 판정 종료

	printf("%s rect_filter error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count/ (float)bit_num *100);		//파일 이름, 에러비트갯수, 비트에러율 출력
}


/*
input#4의 
최적의 필터
*/
void tri_filter(char file_name[20], int opt, int bit_num) {	//파일이름,기준값,비트수 받음
	FILE* fin;
	FILE* fbit;
	fopen_s(&fbit, "bit.dat", "rt");
	fopen_s(&fin, file_name, "rt");			//rect matched filter와 마찬가지로 파일 읽는 과정
	float input[10] = { 0.0, };				//파형 저장
	float filter[10] = { 0,6,10,12,15,15,12,10,6,0 };		//최적의 필터 구현을 위해 기준 bit파형과 모양이 같은 필터
	float sum = 0;	//계산값
	int detect;		//계산값이 기준값 보다 크면 1 작으면 0
	int bit;		//실제 bit
	int i, k;		//for문용
	float error_count = 0;	//에러 비트 갯수

	for (i = 0; i < bit_num; i++) {			//bit수만큼 반복
		for (k = 0; k < 10; k++) {			//bit파형과 필터를 곱한 후 더함
			fscanf_s(fin, "%f", &input[k]);
			sum += filter[k]*input[k];
		}
		if (sum > opt)		//계산값이 기준보다 크면 1 작으면 0
			detect = 1;
		else if(sum < opt) 
			detect = 0;
		fscanf_s(fbit, "%d", &bit);	//실제 bit와 비교후 작으면 0 크면 1
		if (detect != bit)
			error_count++;
		sum = 0;	//계산값 0 초기화
	}
	printf("%s tri_filter error_count: %d, error_rate: %.1f%%\n", file_name,(int)error_count, (error_count / (float)bit_num * 100));	//파일 이름, 에러비트갯수, 비트에러율 출력
}




