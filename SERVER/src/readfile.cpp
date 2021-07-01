#include "../include/readfile.h"
#include "../include/Database.h"
extern Database db;
int read(string filename, string &content)
{
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();
        return myOK;
    }
    else
        return myERROR;
}
// 閫掑綊璋冪敤
int userfiles(int userid, string rootdir, queue<file> &files, bool is_root)
{
    if (!is_root && !db.directoryIsBind(userid, rootdir))
        return myOK;
    DIR *dir;
    struct dirent *ptr;
    string x, dirPath;
    cout << rootdir << endl;
    dir = opendir(rootdir.c_str());      //鎵撳紑涓€涓洰褰�
    while ((ptr = readdir(dir)) != NULL) //寰幆璇诲彇鐩綍鏁版嵁
    {
        if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
            continue;
        file ftmp;
        ftmp.filename = ptr->d_name;
        ftmp.is_file = ptr->d_type == DT_DIR ? false : true;
        ftmp.path = rootdir + "/" + ftmp.filename;
        cout << ftmp.path << endl;
        if (ptr->d_type == DT_DIR)
        {
            files.push(ftmp);
            userfiles(userid, ftmp.path, files);
        }
        else
        {
            FILE *fp = NULL;
            string getmd5 = "md5sum " + ftmp.path;
            if ((fp = popen(getmd5.c_str(), "r")) != NULL)
            {
                char md5res[33];
                fgets(md5res, sizeof(md5res), fp);
                ftmp.md5 = md5res;
                pclose(fp);
            }
            files.push(ftmp);
        }
    }
    closedir(dir); //鍏抽棴鐩綍鎸囬拡
    return myOK;
}
int writefile(string filename, string content)
{
    ofstream outfile(filename, ios::out | ios::app);
    if (!outfile.is_open())
        return myERROR;
    cout << "写入" << filename << endl;
    outfile << content;
    outfile.close();
    return myOK;
}

int renewfile(string filename, string content)
{
    remove(filename.c_str());
    ofstream outfile(filename, ios::out);
    if (!outfile.is_open())
        return myERROR;
    cout << "renewfile: " << filename << endl;
    outfile << content;
    outfile.close();
    return myOK;
}