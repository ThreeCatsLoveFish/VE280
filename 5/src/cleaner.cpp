/**
 * @file cleaner.cpp
 * @author Zhimin Sun
 * @brief LaTeX Code Cleaner
 * @date 2020-11-26
 * @course 2020FA VE280
 */
#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;

static const size_t NON_CMD = 0;
static const size_t ADD_CMD = 1;
static const size_t DEL_CMD = 2;
static const size_t EMP_CMD = 3;

struct Command
{
    size_t        strPos;
    const size_t  cmdLen;
    const size_t &cmdType;

    /* No command */
    Command() : strPos(NON_CMD), cmdLen(NON_CMD), cmdType(NON_CMD)
    {}
    /* Empty command */
    Command(const size_t &Pos) : strPos(Pos), cmdLen(1), cmdType(EMP_CMD)
    {}
    /* Add or Del command */
    Command(const size_t &Pos, const size_t &type, const size_t &len)
        : strPos(Pos), cmdLen(len), cmdType(type)
    {}
    /* Copy command */
    Command(const Command &obj)
        : strPos(obj.strPos), cmdLen(obj.cmdLen), cmdType(obj.cmdType)
    {}
};

class Cleaner
{
private:
    string *addList;
    string *delList;
    size_t  addSize;
    size_t  delSize;

    /**
     * @brief Get the index of first valid '%' in cmd.
     *
     * @param cmd   String of input.
     * @param start Index of start.
     * @return      If found, 0 <= pos < `len`, else return `len`.
     */
    size_t findComment(const string &cmd, const size_t &start = 0) const
    // EFFECTS: Get the index of first valid '%' in cmd.
    {
        size_t len = cmd.length();

        for (size_t i = start; i < len; i++) {
            i = cmd.find('%', i);
            if (i >= len) {
                break;
            } else if (i == 0 || cmd[i - 1] != '\\') {
                return i;
            }
        }
        return len;
    }

    /**
     * @brief  Determine whether sign is inside '%' and '\n' (comment)
     *
     * @param cmd     String of the LaTeX code
     * @param start   Index of start.
     * @param index   index of signs
     * @return true   Is comment
     * @return false  Not comment
     */
    bool isComment(const string &cmd, const size_t &index,
                   const size_t &start = 0) const
    // EFFECTS: Determine whether this is comment
    {
        size_t comPos = findComment(cmd, start);

        if (comPos == cmd.length()) {
            return false;
        } else {
            size_t breakPos = cmd.find('\n', comPos);

            if (comPos > index) {
                return false;
            } else if (breakPos > index) {
                return true;
            } else {
                return isComment(cmd, index, breakPos);
            }
        }
    }

public:
    Cleaner()
    {
        /* Input add commands. */
        cin >> addSize;
        addList = new string[addSize];
        for (size_t i = 0; i < addSize; i++) {
            cin >> addList[i];
        }
        cin.get();
        /* Input del commands. */
        cin >> delSize;
        delList = new string[delSize];
        for (size_t i = 0; i < delSize; i++) {
            cin >> delList[i];
        }
        cin.get();
    }

    ~Cleaner()
    {
        delete[] addList;
        delete[] delList;
    }

    /**
     * @brief Get the detail of command.
     *
     * @param cmd   String of input.
     * @param start Index of start.
     * @return      Detail of command
     */
    Command leftBrace(const string &cmd, const size_t &start = 0) const
    // EFFECTS: Get the detail of command with left brace.
    {
        const size_t maxlen   = cmd.length();
        size_t       addPos   = maxlen;
        size_t       delPos   = maxlen;
        size_t       empPos   = maxlen;
        size_t       len      = maxlen;
        size_t       addIndex = 0;
        size_t       delIndex = 0;

        for (size_t index = 0; index < addSize; index++) {
            for (size_t i = start; i < maxlen; i++) {
                i = cmd.find(addList[index] + "{", i);
                if (i >= maxlen) {
                    break;
                } else if (!isComment(cmd, i) && i < addPos) {
                    addIndex = index;
                    addPos   = i;
                    len      = min(i, len);
                    break;
                }
            }
        }
        for (size_t index = 0; index < delSize; index++) {
            for (size_t i = start; i < maxlen; i++) {
                i = cmd.find(delList[index] + "{", i);
                if (i >= maxlen) {
                    break;
                } else if (!isComment(cmd, i) && i < delPos) {
                    delIndex = index;
                    delPos   = i;
                    len      = min(i, len);
                    break;
                }
            }
        }
        for (size_t i = start; i < maxlen; i++) {
            i = cmd.find("{", i);
            if (i >= maxlen) {
                break;
            } else if ((i == 0 || cmd[i - 1] != '\\') && !isComment(cmd, i)) {
                empPos = i;
                len    = min(i, len);
                break;
            }
        }
        if (len == addPos && len != maxlen) {
            return Command(addPos, ADD_CMD, addList[addIndex].length() + 1);
        } else if (len == delPos && len != maxlen) {
            return Command(delPos, DEL_CMD, delList[delIndex].length() + 1);
        } else if (len == empPos && len != maxlen) {
            return Command(empPos);
        } else {
            return Command();
        }
    }

    /**
     * @brief Get the index of first valid '}' in cmd.
     *
     * @param cmd   String of input.
     * @param start Index of start.
     * @return      If found, 0 <= pos < `len`, else return `len`.
     */
    size_t rightBrace(const string &cmd, const size_t &start = 0) const
    // EFFECTS: Get the index of first valid '}' in cmd.
    {
        size_t len = cmd.length();

        for (size_t i = start; i < len; i++) {
            i = cmd.find('}', i);
            if (i >= len) {
                break;
            } else if ((i == 0 || cmd[i - 1] != '\\') && !isComment(cmd, i)) {
                return i;
            }
        }
        return len;
    }
};

/**
 * @brief Get the Content of LaTeX code.
 *
 * @return    String that will be written in
 */
static string
getContent(void)
// EFFECTS: Get the Content of LaTeX code.
// MODIFIES: code
{
    string code;
    string content;

    while (getline(cin, content)) {
        if (content == "") {
            continue;
        }
        code = code + content + '\n';
    }
    return code;
}

int
main(void)
{
    Cleaner        list;
    Dlist<Command> braces;
    string         code = getContent();

    while (true) {
        Command first = list.leftBrace(code);
        size_t  end   = first.strPos;

        /* No command. */
        if (first.cmdType == NON_CMD) {
            break;
        }
        braces.insertBack(new Command(first));
        while (!braces.isEmpty()) {
            Command *top   = braces.removeBack();
            Command  left  = list.leftBrace(code, top->strPos + top->cmdLen);
            size_t   right = list.rightBrace(code, top->strPos + top->cmdLen);

            if (top->cmdType == NON_CMD) {
                delete top;
                try {
                    top = braces.removeBack();
                } catch (emptyList) {
                    break;
                }
            }

            if (left.cmdType == NON_CMD || left.strPos > right) {
                /* Handle previous command. */
                if (top->cmdType == DEL_CMD) {
                    code = code.substr(0, top->strPos) + code.substr(right + 1);
                    end  = top->strPos;
                } else if (top->cmdType == ADD_CMD) {
                    int length = right - (top->strPos + top->cmdLen);
                    if (length > 0) {
                        code = code.substr(0, top->strPos) +
                               code.substr(top->strPos + top->cmdLen, length) +
                               code.substr(right + 1);
                    } else {
                        code = code.substr(0, top->strPos) +
                               code.substr(right + 1);
                    }
                    end = top->strPos + length;
                } else if (top->cmdType == EMP_CMD) {
                    end = right;
                    braces.insertBack(new Command(right, NON_CMD, 1));
                }
                delete top;
            } else {
                /* A new command. */
                braces.insertBack(top);
                braces.insertBack(new Command(left));
            }
        }
        if (end > 0) {
            cout << code.substr(0, end);
            code = code.substr(end);
        }
    }
    cout << code;
    return 0;
}
