#include "./readfile.h"
int read(const char* filename,string &content)
{
    ofstream out;
    out.open(filename, ios::out);
    if(!out.is_open())
        return -1;
    out << content;
    out.close();
    return 0;
}
// 递归调用
int userfiles(const char* rootdir,vector<file>&files){
    DIR * dir;
    struct dirent * ptr;
    string x,dirPath;
    dir = opendir(rootdir); //打开一个目录
    while((ptr = readdir(dir)) != NULL) //循环读取目录数据
    {
        if((strcmp(ptr->d_name,".") == 0) || (strcmp(ptr->d_name,"..")==0))
            continue;
        file ftmp;
        ftmp.filename=ptr->d_name;
        ftmp.is_file=ptr->d_type==DT_DIR?false:true;
        ftmp.path = rootdir+"/"+ftmp.filename;
        files.push_back(ftmp);
        if(ptr->d_type==DT_DIR){
            userfiles(ftmp.path,files);
        }
        else{
            
        }
    }
    closedir(dir);//关闭目录指针
}