#include <iostream>
#include <string>
using namespace std;

class TextEditor // Component
{
public:
    virtual void write(const string &words) = 0;
    virtual ~TextEditor() = default;
};

class BasicEditor : public TextEditor // Concrete Component
{
public:
    void write(const string &words) override
    {
        cout << "Performing Basic Editor Functionality!" << endl;
        cout << "Text: " << words << endl;
    }
};

class EditorDecorator : public TextEditor // Decorator
{
public:
    EditorDecorator(TextEditor *editor) : editor_(editor) {}
    void write(const string &words) override
    {
        editor_->write(words); // Delegate to the component
    }
protected:
    TextEditor *editor_;
};

class SpellCheckerDecorator : public EditorDecorator // Concrete Decorator
{
public:
    SpellCheckerDecorator(TextEditor *editor) : EditorDecorator(editor) {}
    void write(const string &words) override
    {
        EditorDecorator::write(words); // Write text
        spellCheck(words); // Add spell checking
    }
private:
    void spellCheck(const string &words)
    {
        cout << "Performing the spell checking here!!" << endl;
    }
}; // Missing semicolon fixed here

int main()
{
    TextEditor *editor = new BasicEditor();
    editor->write("CSE-327");

    cout << "\nAfter performing Decorator wrapping:\n";
    TextEditor *editor2 = new BasicEditor();
    TextEditor *spellChecker = new SpellCheckerDecorator(editor2);
    spellChecker->write("CSE-327");

    // Clean up dynamically allocated memory
    delete editor;
    delete spellChecker;

    return 0;
}
