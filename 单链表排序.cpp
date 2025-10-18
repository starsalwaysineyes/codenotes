//单链表排序 - 使用归并排序算法
#include<iostream>
#include<vector>  
using namespace std;

// 链表节点结构体模板
template<typename T>
struct ListNode{
    T data;                    // 节点数据
    ListNode<T>* next;        // 指向下一个节点的指针

    // 构造函数1：只传入数据值
    ListNode(T val):data(val),next(nullptr){}

    // 构造函数2：传入数据值和下一个节点指针
    ListNode(T val,ListNode<T>* next):data(val),next(next){}

    // 析构函数：递归删除整个链表
    ~ListNode(){
        if(next){
            delete next;
        }
    }
};

// 根据数组创建链表的函数
template<typename T>
ListNode<T>* createList(const vector<T>& arr){
    ListNode<T>* head = nullptr;  // 链表头指针
    ListNode<T>* tail = nullptr;  // 链表尾指针
    for(const T& val : arr){
        ListNode<T>* newNode = new ListNode<T>(val);  // 创建新节点
        if(head == nullptr){
            head = newNode;  // 第一个节点作为头节点
            tail = newNode;
        }else{
            tail->next = newNode;  // 将新节点连接到链表尾部
            tail = newNode;        // 更新尾指针
        }
    }
    tail->next = nullptr;  // 确保最后一个节点的next为nullptr
    return head;
}

// 打印链表内容的函数
template<typename T>
void printList(ListNode<T>* head){
    ListNode<T>* current = head;  // 当前遍历的节点

    while(current != nullptr){
        cout << current->data << " ";  // 输出当前节点的数据
        current = current->next;       // 移动到下一个节点
    }
    cout << endl;
}

// 归并排序主函数 - 使用分治法
template<typename T>
ListNode<T>* sortList(ListNode<T>* head){
    // 递归终止条件：空链表或只有一个节点
    if(head == nullptr || head->next == nullptr){
        return head;
    }
    
    // 使用快慢指针找到链表中点
    ListNode<T>* slow = head;      // 慢指针
    ListNode<T>* fast = head->next; // 快指针
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;         // 慢指针每次移动一步
        fast = fast->next->next;   // 快指针每次移动两步
    }
    
    // 分割链表
    ListNode<T>* mid = slow;           // 中点
    ListNode<T>* right = mid->next;   // 右半部分
    mid->next = nullptr;              // 断开链表
    
    // 递归排序左右两部分
    ListNode<T>* left = sortList(head);
    ListNode<T>* rightSorted = sortList(right);
    
    // 合并两个已排序的链表
    return merge(left, rightSorted);
}

// 合并两个已排序链表的函数
template<typename T>
ListNode<T>* merge(ListNode<T>* left, ListNode<T>* right){
    ListNode<T>* dummy = new ListNode<T>(0);  // 创建虚拟头节点
    ListNode<T>* current = dummy;             // 当前合并位置
    
    // 比较两个链表的节点，将较小的节点加入结果链表
    while(left != nullptr && right != nullptr){
        if(left->data < right->data){
            current->next = left;   // 左链表节点较小
            left = left->next;      // 移动左链表指针
        }else{
            current->next = right;  // 右链表节点较小
            right = right->next;    // 移动右链表指针
        }
        current = current->next;    // 移动合并位置指针
    }
    
    // 将剩余节点连接到结果链表
    current->next = left != nullptr ? left : right;
    
    return dummy->next;  // 返回合并后的链表头节点
}


// 主函数 - 测试单链表排序
int main(){
    // 创建测试数据
    vector<int> arr = {4, 2, 1, 3, 5};
    
    // 创建链表
    ListNode<int>* head = createList(arr);
    
    // 打印原始链表
    cout << "原始链表: ";
    printList(head);
    
    // 排序链表
    head = sortList(head);
    
    // 打印排序后的链表
    cout << "排序后: ";
    printList(head);
    
    // 释放内存
    delete head; 
    
    return 0;
}