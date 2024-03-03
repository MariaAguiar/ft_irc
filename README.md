# ft_irc
## Auto-formater
### Install clang-format
```bash
sudo apt-get install clang-format
```
Once you have installed Clang-format, you can verify the installation by running the following command:
```bash
clang-format --version
clang-format version 10.0.0-4ubuntu1
```
### Using Clang-format with VSCode
Install clang-format extension on VSCode-> https://marketplace.visualstudio.com/items?itemName=xaver.clang-format

To automatically save a file on save, add the following to your vscode settings file:
```json
{
    "editor.formatOnSave": true
}
```
