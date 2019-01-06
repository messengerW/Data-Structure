#include <stdio.h>

#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )		// ���鳤��
#define swap(a,b) (a^=b,b^=a,a^=b)

/*
��N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
NΪ�����±�����ֵ���������е�1������Ӧ��NΪ0��
 */
void maxheap_down(int a[], int start, int end)
{
    int c = start;            // ��ǰ�ڵ��λ��
    int l = 2*c + 1;       	  // ���ӵ�λ��
    int tmp = a[c];           // ��ǰ�ڵ�Ĵ�С
    for (; l <= end; c=l,l=2*l+1)
    {
        // "l"�����ӣ�"l+1"���Һ���
        if ( l < end && a[l] < a[l+1])
            l++;       		 // ������������ѡ��ϴ��ߣ���m_heap[l+1]
        if (tmp >= a[l])
            break;      	 // ��������
        else           		 // ����ֵ
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}
/*
������(��С����)
 */
void heap_sort_asc(int a[], int n)
{
    int i;
    // ��(n/2-1) --> 0��α���������֮�󣬵õ���������һ���󶥶ѡ�
    for (i = n / 2 - 1; i >= 0; i--)
        maxheap_down(a, i, n-1);
    // �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for (i = n - 1; i > 0; i--)
    {
        // ����a[0]��a[i]��������a[i]��a[0...i]�����ġ�
        swap(a[0], a[i]);
        // ����a[0...i-1]��ʹ��a[0...i-1]��Ȼ��һ�����ѡ�
        // ��֤a[i-1]��a[0...i-1]�е����ֵ��
        maxheap_down(a, 0, i-1);
    }
}
/*
��N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
NΪ�����±�����ֵ���������е�1������Ӧ��NΪ0��
 */
void minheap_down(int a[], int start, int end)
{
    int c = start;           	 // ��ǰ�ڵ��λ��
    int l = 2*c + 1;        	 // ���ӵ�λ��
    int tmp = a[c];              // ��ǰ�ڵ�Ĵ�С
    for (; l <= end; c=l,l=2*l+1)
    {
        // "l"�����ӣ�"l+1"���Һ���
        if ( l < end && a[l] > a[l+1])
            l++;        // ������������ѡ���С��
        if (tmp <= a[l])
            break;      // ��������
        else            // ����ֵ
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}

/*
������(�Ӵ�С)
 */
void heap_sort_desc(int a[], int n)
{
    int i;
    // ��(n/2-1) --> 0��α���ÿ������֮�󣬵õ�������ʵ������һ��С���ѡ�
    for (i = n / 2 - 1; i >= 0; i--)
        minheap_down(a, i, n-1);
    // �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for (i = n - 1; i > 0; i--)
    {
        // ����a[0]��a[i]��������a[i]��a[0...i]����С�ġ�
        swap(a[0], a[i]);
        // ����a[0...i-1]��ʹ��a[0...i-1]��Ȼ��һ����С�ѡ�
        // ������֤a[i-1]��a[0...i-1]�е���Сֵ��
        minheap_down(a, 0, i-1);
    }
}

void main()
{
    int i;
    int a[] = {2,3,9,4,70,11,6,1,10,5,8};
    int ilen = LENGTH(a);
    printf("before sort:");
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");
	printf("С����:");
    heap_sort_asc(a, ilen);         // ��������
	for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
	printf("\n�󶥶�:");
    heap_sort_desc(a, ilen);        // ��������
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");
}
