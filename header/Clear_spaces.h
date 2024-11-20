#ifndef CLEAR_SPACES_H
#define CLEAR_SPACES_H

void trim(char *str) {
    // Xóa khoảng trắng đầu
    char *start = str;// con trỏ start trỏ đến đầu chuỗi str
    while(*start == ' ')
        start++; // nếu ký tự đầu tiên là khoảng trắng thì con trỏ start sẽ trỏ đến ký tự tiếp theo
    //------------------------    
    if(start != str) 
    {
        memmove(str, start, strlen(start) + 1);// hàm này để copy nội dung từ start đến cuối chuỗi str với độ dài là strlen(start) + 1
    }// end if
    //------------------------
    // Xóa khoảng trắng cuối
    char *end = str + strlen(str) - 1;// con trỏ end trỏ đến cuối chuỗi str
    while(end > str && *end == ' ') 
        end--; // end > str là điều kiện để end không trỏ về đầu chuỗi, *end == ' ' là điều kiện để ký tự cuối cùng là khoảng trắng thì con trỏ end sẽ trỏ về ký tự trước đó
    *(end + 1) = '\0'; // đặt ký tự cuối cùng là null
}

#endif// end CLEAR_SPACES_H