import csv
import sys


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    
    database = []
    # Load CSV data into emory
    filename = sys.argv[1]
    with open(filename, 'r') as file:
        reader = csv.DictReader(file)
        columns = len(reader.fieldnames)
        # Iterate through the file to extract and organize the data from the csv into
        # a dictionary.
        for row in reader:
            name = row["name"]
            # this portion of the script with deal with the entries with 3 STR's
            if columns == 4:
                AGATC = int(row["AGATC"])
                AATG = int(row["AATG"])
                TATC = int(row["TATC"])
                database.append({'name': name, 'AGATC': AGATC, 'AATG': AATG, 'TATC': TATC})
            # this portion of the script with deal with the entries with 8 STR's
            elif columns == 9:
                AGATC = int(row["AGATC"])
                TTTTTTCT = int(row["TTTTTTCT"])
                AATG = int(row["AATG"])
                TCTAG = int(row["TCTAG"])
                GATA = int(row["GATA"])
                TATC = int(row["TATC"])
                GAAA = int(row["GAAA"])
                TCTG = int(row["TCTG"])
                database.append({'name': name, 'AGATC': AGATC, 'TTTTTTCT': TTTTTTCT, 'AATG': AATG,
                                'TCTAG': TCTAG, 'GATA': GATA, 'TATC': TATC, 'GAAA': GAAA, 'TCTG': TCTG})
    # Open and read the unknown DNA sequence
    DNAMatch = False
    sequencefile = open(sys.argv[2], 'r')
    sequence = sequencefile.read()
    # This section of the script will extract the maximum number of sequential appearances of
    # of the different STR's for the database with 3 STR's.
    if columns == 4:
        AGATC = maxSTRrepeats(sequence, 'AGATC')
        AATG = maxSTRrepeats(sequence, 'AATG')
        TATC = maxSTRrepeats(sequence, 'TATC')
        # And then if will compare it to the sequence of STR's with the database with the 
        # differnt persons, if there is a match, it will print the name of the person
        for i in range(0, len(database), 1):
            if database[i]['AGATC'] == AGATC:
                if database[i]['AATG'] == AATG:
                    if database[i]['TATC'] == TATC:
                        print(database[i]['name'])
                        DNAMatch = True
    # This section of the script will extract the maximum number of sequential appearances of
    # of the different STR's for the database with 8 STR's.
    if columns == 9:
        AGATC = maxSTRrepeats(sequence, 'AGATC')
        TTTTTTCT = maxSTRrepeats(sequence, 'TTTTTTCT')
        AATG = maxSTRrepeats(sequence, 'AATG')
        TCTAG = maxSTRrepeats(sequence, 'TCTAG')
        GATA = maxSTRrepeats(sequence, 'GATA')
        TATC = maxSTRrepeats(sequence, 'TATC')
        GAAA = maxSTRrepeats(sequence, 'GAAA')
        TCTG = maxSTRrepeats(sequence, 'TCTG')
        # And then if will compare it to the sequence of STR's with the database with the 
        # differnt persons, if there is a match, it will print the name of the person
        for i in range(0, len(database), 1):
            if database[i]['AGATC'] == AGATC:
                if database[i]['TTTTTTCT'] == TTTTTTCT:
                    if database[i]['AATG'] == AATG:
                        if database[i]['TCTAG'] == TCTAG:
                            if database[i]['GATA'] == GATA:
                                if database[i]['TATC'] == TATC:
                                    if database[i]['GAAA'] == GAAA:
                                        if database[i]['TCTG'] == TCTG:
                                            print(database[i]['name'])
                                            DNAMatch = True
    # If the DNA sequence is not in the DATABASE, "No match will be displayed"
    if DNAMatch == False:
        print("No match")


def maxSTRrepeats(DNASeq, STR):
    maxSeq = 0
    seq = 0
    STRlen = len(STR)
    DNASeqlen = len(DNASeq)
    # 0. This line extract holds the number of appearances of the STR in the DNASeq, it
    #    will be used to search for this apperances and extract the index, 
    # 1. if the index is 0, a counter will be increased because it means that is either 
    #    the first appearance of the STR in the DNASeq or its a consecutive appearance.
    # 2. else, the index is different than 0, it means that the appearance of the STR is not
    #    consecutive, therefore the counter of appearances will be reset to 0.
    # 3. Then, the appearance counter will be compared to
    #    the counter that holds the value for the max consecutive appearances, if its bigger,
    #    it will replace its value.
    # 4. At the end of every iteration cycle, the DNA sequence will be split, from the last
    #    index of the last appearance of the STR + the length of the STR

    # 0
    totalAppears = DNASeq.count(STR)
    for i in range(0, totalAppears, 1):
        index = DNASeq.find(STR)
        # 1
        if index == 0:
            seq += 1
        # 2
        else:
            seq = 1
        # 3
        if seq > maxSeq:
            maxSeq = seq
        DNASeq = DNASeq[index+STRlen:DNASeqlen]
    return maxSeq


if __name__ == "__main__":
    main()