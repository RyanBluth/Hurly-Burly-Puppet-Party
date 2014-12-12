#pragma once

#include <vector>

class Command;
class CompressedCommand;
class ConsoleEntry;

class CommandProcessor{
public:
	CommandProcessor(void);
	~CommandProcessor(void);

	bool executeCommand(Command * c);
	// Runs "unexecute()" on the last command in the undoStack, pops it off the stack, and pushes it onto the redoStack
	void undo();
	// Runs "unexecute()" on every command in the undoStack, pops them off the stack, and pushes it onto the redoStack
	void undoAll();
	// Runs "execute()" on the last command in the redoStack, pops it off the stack, and pushes it onto the undoStack
	void redo();
	// Runs "execute()" on every command in the redoStack, pops them off the stack, and pushes it onto the undoStack
	void redoAll();
	// Deletes and clears the contents of the undo and redo stacks
	void reset();
	
	void startCompressing();
	void endCompressing();

	std::vector<ConsoleEntry> consoleEntries;
private:
	std::vector<Command *> undoStack;
	std::vector<Command *> redoStack;

	void log(std::string _message);
	void warn(std::string _message);
	void error(std::string _message);
	
	CompressedCommand * currentCompressedCommand;
};
