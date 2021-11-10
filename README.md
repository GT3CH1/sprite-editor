# Sprite Editor
A sprite editor written in QT.

## Naming conventions
Branches shall be named similary to the task they are created.  For example, the ActionState task branch will be named action-state.

## Some helpful git commands
- First, navigate to where you cloned the project to (For example In Documents/Programming/CS3505/assignment8)
`cd /mnt/c/Users/gcpease/Documents/Programming/CS3505/assignment8` gcpease is the username I used to sign into computer. Replace it with yours. Please hit the tab key a few times to see autocomplete options.

## Code Conventions
- Tabs, not spaces.
- camelCase for method names.
- CONSTS are capitalized, unless they are parameters. They will ALSO\_HAVE an underscore if they are multiple words
- Curly braces are on a new line.
- Classes will have TheFirstLetterOfEveryWord capitalized.
- Files will have allthewordsinlowercase.
- Doc-comments will be on every method and class in javadoc style.
- Member variables will be commented with a small in-line comment describing their use.
- Classess will have a short doc-style comment with the author(s) name, date created, and a short description of what that class does (Even if painstakingly obvious). This will be done in the CPP file, and not the header file.
- TODO's will have to have the username of the programmer listed, IE `TODO(gcpease): Fix really bad bug`
- In header files, private will be before public.

## Commit Conventions
- When commiting, please add a tag infront specifying what commit number this change is out of how many you think it will
take. If you do not have a logical guess, just add a question mark. Example: `[1/2] Fix UI showing green and not pink`
- When you are done working on an assignment, create a pull request so the changes can be reviewed and eventually 

## Some helpful git stuff
- To create a new branch, type in
`git branch <branch-name>` where <branch-name> follows the naming conventions.

- To start working in a different branch, type in
  `git checkout <branch-name>`

- To update your current branch, type in
  `git fetch` followed by a `git pull`

- To set an upstream branch (so all you have to do to update is `git fetch` and `git pull` type in:
  `git --set-upstream origin <your-branch>` If you do not do this, you can just type `git push origin <branch-name>

### Advanced git stuff
- To merge a branch, type in
  `git fetch` followed by `git pull <branch-name>`. Chances are you'll have conflicts everywhere. This is why you 
  shoud really not be doing this consistently, as it does get very painful.
- To create a pull request, go to the webpage for the github repository, navigate to your branch and click the
giant green "Compare & pull request" button. Please appropriately title your pull request, and reference the task ID in the description (ie, ActionState was PR \#2). Assign your buddy and probably another person to review your code to see if it is up to spec.

## Other important information
  - Do not push directly to main. At all, please.
  - Please run this command: `git config --global core.autocrlf true` it will prevent line endings screwing everything.
    - If you do not run this command, please set your line-ending style to Unix in QT preferences.
## Using WSL
  - WSL is a VERY powerful tool. One of my favorite things to do is to absolutey press the tab key to autocomplete.
