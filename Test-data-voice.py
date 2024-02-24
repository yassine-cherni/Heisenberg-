from assistant import Helper
import time 
from datetime import datet
assistant=Helper()
if __name__ == '__main__': 
    assistant.speak('Hi I am Yassine your assistante. i can search on wikipedia and write some note for you, how can i help you ', 140)

    while True:
        # Parse as a list
        # query = 'computer say hello'.split()
        query = assistant.parscommand().lower().split()

        if query[0] in assistant.activationword and len(query) > 1:
            query.pop(0)
            # Wikipedia
            if 'wikipedia' in query:
                pos= [ind for ind, v in enumerate(query) if v == 'wikipedia' ]
                query = ' '.join(query[pos[0]:])
                assistant.speak('Querying the universal databank')
                time.sleep(2)
                assistant.speak(assistant.search_wikipedia(query))
            # Note taking
            if query[0] == 'note':
                assistant.speak('Ready to record your note')
                newNote = assistant.parscommand().lower()
                now = datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
                with open('note_%s.txt' % now, 'w') as newFile:
                    newFile.write(now)
                    newFile.write(' ')
                    newFile.write(newNote)
                assistant.speak('Note written')
            if query[0] == 'bye':
                assistant.speak('Goodbye')
                break
