#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}


// Given a poll data string pollData, determines if the string
// has proper pollData syntax
// Returns	true if the string is valid
//			false if the string is not valid

bool hasProperSyntax(string pollData) {
	for (unsigned int i = 0; i < pollData.size(); i++) { // iterates through pollData using a for loop

		// creates state string to pass to isValidUppercaseStateCode()
		// to check if the state forcast begins with a state code
		string state = string() + char(toupper(pollData[i])) + char(toupper(pollData[i + 1]));

		if (!isValidUppercaseStateCode(state)) {
			return false; // returns false if first two chars of state forecast do not form a state code
		}
		i += 2; // moves index past state code

		// checks to make sure party results follow state code in each forecast
		for (; (isalpha(pollData[i]) || isdigit(pollData[i])) && i < pollData.size(); i++) { // iterates through party results using for loop
			if (!isdigit(pollData[i]))
				return false; // returns false if party result doesn't start with digit
			int valueLen = 0;
			for (; isdigit(pollData[i]); i++, valueLen++); // iterates through digits in party result
			if (valueLen > 2)
				return false; // returns false if more than 2 digits in a row in party result
			if (!isalpha(pollData[i]) || isalpha(pollData[i + 1])) {
				return false; // returns false if party code is incorrect (either >1 char length or non alpha character)
			}
		}
		if (pollData[i] != ',' && i < pollData.size())
			return false; // only valid end to state forecast is a comma or end of string
	}

	return true; // only returns true if all conditions are met
}


// Given a poll data string pollData and a character party, finds the 
// number of seats for that party within pollData
// Returns	0 if executes successfully
//			1 if the pollData string does not have proper syntax
//			2 if the party character is not valid

int tallySeats(string pollData, char party, int& seatTally) {
	if (!hasProperSyntax(pollData))
		return 1; // returns 1 if syntax is invalid
	if (!isalpha(party))
		return 2; // returns 2 if party character is invalid

	// makes pollData and party uppercase to facilitate looking for equality between them
	for (unsigned int i = 0; i < pollData.size(); i++) {
		pollData[i] = toupper(pollData[i]);
	}
	party = toupper(party);

	int totalVotes = 0;
	for (unsigned int i = 0; i < pollData.size(); i++) { // iterates through pollData
		i += 2; // skips state codes
		for (; isalpha(pollData[i]) || isdigit(pollData[i]); i++) { // iterates through party results

			// accumulates votes for current party result and adds to totalVotes
			// if the party in the party result matches the party argument
			int votes = 0;
			for (; isdigit(pollData[i]); votes = (10 * votes) + pollData[i] - '0', i++); // calculates votes found in party result
			if (pollData[i] == party) {
				totalVotes += votes;
			}
		}
	}

	seatTally = totalVotes;	// sets seatTally to the total vote count
	return 0; // returns 0 if the function executed successfully
}

// Tester code; runs hard coded given cases including many edge cases
// and hopefully testing all needed cases
// Returns	0 if executes successfully
//			i where i is the case index if the case fails
int tester(int i) {

	const int DEFAULT_SEAT_VALUE = -999;
	int v = DEFAULT_SEAT_VALUE;

	switch (i) {
	default: {
		cout << "Bad argument; no case for value " << i << "." << endl;
	}
			 break;
	case 1: {
		if (!hasProperSyntax(""))
			return i;
	}
			break;
	case 2: {
		if (!hasProperSyntax("VT"))
			return i;
	}
			break;
	case 3: {
		if (hasProperSyntax("cA#"))
			return i;
	}
			break;
	case 4: {
		if (hasProperSyntax("iL41de2re"))
			return i;
	}
			break;
	case 5: {
		if (hasProperSyntax("CA432d2r"))
			return i;
	}
			break;
	case 6: {
		if (!hasProperSyntax("CA43d,IL3d"))
			return i;
	}
			break;
	case 7: {
		if (!hasProperSyntax("CA43d2r"))
			return i;
	}
			break;
	case 8: {
		if (hasProperSyntax("CA432d2r,IL3d2r1i,VT,MN"))
			return i;
	}
			break;
	case 9: {
		if (hasProperSyntax("CA432d2r,IL3d2r1#,VT,MN"))
			return i;
	}
			break;
	case 10: {
		if (hasProperSyntax("CA432d2r,IL3d2r221g,VT,MN"))
			return i;
	}
			 break;
	case 11: {
		if (!(tallySeats("3F1F3", 'g', v) == 1 && v == DEFAULT_SEAT_VALUE))
			return i;
	}
			 break;
	case 12: {
		if (!(tallySeats("cA3d", '3', v) == 2 && v == DEFAULT_SEAT_VALUE))
			return i;
	}
			 break;
	case 13: {
		if (!(tallySeats("TX38R2G", 'R', v) == 0 || v == 38))
			return i;
	}
			 break;
	case 14: {
		if (!(tallySeats("tX38r2g", 'g', v) == 0 || v == 2))
			return i;
	}
			 break;
	case 15: {
		if (!(tallySeats("CA43d,TX2g", 'g', v) == 0 || v == 2))
			return i;
	}
			 break;
	case 16: {
		if (!(tallySeats("ID4R11G2D,RI4D,ND3R1D,CT,OR7D1R", 'R', v) == 0 || v == 8))
			return i;
	}
			 break;
	case 17: {
		if (!(tallySeats("ND3R,CT7D,OR7D,ID4R,SD3R,RI4D", 'd', v) == 0 || v == 21))
			return i;
	}
			 break;
	case 18: {
		if (!(tallySeats("Nd3R,ct7D2g,oR7D,id4r,SD1g3R,Ri4D,Ca43d2r,IL3d2r21g,vT,MN,sD3R,rI4d", 'g', v) == 0 || v == 24))
			return i;
	}
			 break;
	case 19: {
		if (!(tallySeats("", 'D', v) == 0 || v == 0))
			return i;
	}
			 break;
	case 20: {
		if (!(tallySeats("CA43d2r", 'D', v) == 0 || v == 43))
			return i;
	}
			 break;
	case 21: {
		if (!(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D")))
			return i;
	}
			 break;
	case 22: {
		if (!(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D")))
			return i;
	}
			 break;
	}

	return 0;
}


int main()
{
	bool fail = false; // flag that represents if any cases fail
	cout << "Testing given cases..." << endl; // shows that testing has begun

	for (int i = 1; i <= 20; i++) {

		// if a given test fails, prints out which test failed to help troubleshoot
		if (tester(i) != 0) {
			cout << "Test " << i << " failed." << endl;
			fail = true; // sets failure flag to true;
		}
	}

	// prints that all tests completely successfully if they did
	// otherwise prints that at least one test failed but they did complete
	if (!fail)
		cout << "---\nAll tests successfully completed." << endl;
	else
		cout << "---\nAll tests completed with at least one failure." << endl;
}