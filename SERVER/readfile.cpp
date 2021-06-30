#include "./readfile.h"
#include "../database/Database.h"
extern Database db;
int read(const char* filename,string &content)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return myOK;
  }
  else
    return myERROR;
}
// 递归调用
int userfiles(int userid,const char* rootdir,queue<file>&files,bool is_root){
    if(!is_root&&!db.directoryIsBind(userid,rootdir))
        return myOK;
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
        if(ptr->d_type==DT_DIR){
            files.push(ftmp);
            userfiles(userid,ftmp.path,files);
        }
        else{
            FILE *fp=NULL;
            string getmd5="md5sum "+ftmp.path;
            if((fp=popen(getmd5,r))!=NULL){
                char md5res[33];
                fgets(md5res,sizeof(md5res),fp);
                ftmp.md5=md5res;
                pclose(fp);
            }
            files.push(ftmp);
        }
    }
    closedir(dir);//关闭目录指针
}
int writefile(const char*filename,string content){
	FILE* fp = NULL; // 文件指针
	errno_t eResult;
 
	// 以附加方式打开可读/写的文件, 如果没有此文件则会进行创建，然后以附加方式打开可读/写的文件
	eResult = fopen_s(&fp, filename, "a+");
 
	// 打开文件失败
	if (eResult != 0)
		return myERROR;
 
	// 将追加内容写入文件指针当前的位置
	fputs(content.c_str(), fp);
 
	// 最后不要忘了,关闭打开的文件~~~
	fclose(fp);
	return 0;
}