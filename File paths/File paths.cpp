#include <iostream>
#include <string>

using namespace std;

#pragma region Special_Abilities

void ClearScrean() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "\tFile paths" << endl;
}

void Enter() {
    string enter;
    cin.ignore();
    do {
        cout << "Press enter to continue: "; getline(cin, enter);
    } while (!enter.empty());
}
#pragma endregion

enum OS {

    None,
    Windows,
    Linux_macOS

};

OS SpellingCorrectness(string path) {

    if(path.find(':') != string::npos && path.find(':', path.find(':') + 1) == string::npos)
    {
        if (path.find('/') == string::npos)
        {        
            int index{ 0 };
            while(path.find('\\', index) != string::npos)
            {
                if (path.find('\\', index) > 0)
                {
                    if (path.find('\\', index) == index)return None;//Если найден символ / и от его индекса отнять 1, и он будет равен прошлему индексу символа
                    else index = path.find('\\', index) + 1;
                }
                else if (index!= path.size() - 1)index++;
                else return None;
            
            }
            return Windows;

        }else return None;
    
    }
    else if (path[0] == '/')
    {
        if (path.find('\\') != string::npos)return None;
        else {

            int index{ 0 };

            while (path.find('/', index) != string::npos)
            {
                if (path.find('/', index) > 0)
                {
                    if (path.find('/', index) == index)return None;//Если найден символ \ и от его индекса отнять 1, и он будет равен прошлему индексу символа
                    else index = path.find('/', index) + 1;
                }
                else if (index != path.size() - 1)index++;
                else return None;

            }
            return Linux_macOS;
        }


    }
    else return None;


}

string PathWithoutFileName(string path, OS os) {

    if (path.find('.') != string::npos && path.find('.') != path.size() - 1)
    {
        if(os == Windows && path[path.find('.') + 1] == '\\')return "";
        else if (os == Linux_macOS && path[path.find('.') + 1] == '/')return "";
        if (path.find('.') != string::npos && path.find('.') != path.size() - 1)
        {
            int beginPath{ -1 }, endPath{ -1 };

            for (size_t i{ path.size() - 1 }; i >= 0; i--)
            {
                if (os == Windows)
                {
                    if (endPath == -1 && path[i] == '\\')endPath = i;
                    else if (endPath != -1 && path[i] == '\\')
                    {
                        if (endPath > path.find('.'))
                        {
                            beginPath = i;
                            break;
                        }
                        else {
                            beginPath = endPath;
                            endPath = path.size() - 1;
                            break;
                        }
                    }
                }
                else if (os == Linux_macOS)
                {
                    if (endPath == -1 && path[i] == '/')endPath = i;
                    else if (endPath != -1 && path[i] == '/')
                    {
                        if (endPath > path.find('.'))
                        {
                            beginPath = i;
                            break;
                        }
                        else {

                            beginPath = endPath;
                            endPath = path.size() - 1;
                            break;
                        }
                    }
                }
            }
            if (beginPath == -1) return "";

            path.erase(path.begin() + beginPath, path.begin() + endPath + 1);
            return path;
        }

    }
    else return "";

}

string LastNameFolders(string path, OS os) {

    string newPath{ PathWithoutFileName(path, os) }, folder{""};
    
    if(os == Windows)folder.insert(0, newPath, newPath.find_last_of('\\') + 1, newPath.size());
    else if(os == Linux_macOS)folder.insert(0, newPath, newPath.find_last_of('/') + 1, newPath.size());

    return folder;
}

string NameFileWithExtension(string path, OS os) {

   string newPath{ PathWithoutFileName(path, os) }, file{" "};

    if (!newPath.empty()) {

        if (path[path.size() - 1] == '\\' || path[path.size() - 1] == '/')
        {
            file.insert(0, path, newPath.size() + 1, path.size() - newPath.size() - 2);
        }
        else {
            file.insert(0, path, newPath.size() + 1, path.size());
        }
    }

    return file;

}

string NameExtension(string path, OS os) {

    string tempFile{ NameFileWithExtension(path, os) }, extens{ "" };

    if (!tempFile.empty()) {

        if(tempFile[tempFile.size() - 1] != '\\' || tempFile[tempFile.size() - 1] != '/')
        {
            extens.insert(0, tempFile, tempFile.find('.'), path.size() - tempFile.size());
        }
        else {
            extens.insert(0, tempFile, tempFile.find('.'), path.size());
        }

    }
    return extens;
}

string NameFileWithoutExtension(string path, OS os) {

    string newName{ NameFileWithExtension(path, os) }, name{ " " };

    if (!newName.empty()) 
    {
        name.insert(0, newName, 0, newName.find('.'));
    }

    return name;

}

int main()
{
    OS os{None};
    int choice{ 1 };

    do{
    
        string path{ "" };

        ClearScrean();
        cout << "Enter file paths: "; getline(cin, path);
        os = SpellingCorrectness(path);

        if (os != None)
        {
           cout << "Path without file name: " << PathWithoutFileName(path, os) << endl;
           cout << "Last folders: " << LastNameFolders(path, os) << endl;
           cout << "File name with name extension: " << NameFileWithExtension(path, os) << endl;
           cout << "Name extension: " << NameExtension(path,os) << endl;
           cout << "File name without name extension: " << NameFileWithoutExtension(path, os) << endl;

        }
        else cout << "Not the right type!" << endl;

        Enter();

        do {

            ClearScrean();
            cout << "Do you want to enter a new value?\n[1] - Yes\n[2] - No" << endl;

            if (choice >= 1 && choice <= 2)cout << "Enter your choice: ";
            else cout << "There is no such choice!\nEnter your choice again: ";

            cin >> choice;

        } while (choice < 1 || choice > 2);

    
    } while (choice == 1);

    return 0;

}

