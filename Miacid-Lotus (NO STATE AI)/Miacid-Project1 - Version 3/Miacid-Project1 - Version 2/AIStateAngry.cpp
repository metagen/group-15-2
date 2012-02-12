#include "AIStateAngry.h"

AIStateAngry::AIStateAngry(StateStrategy* stateMachine)
{
	this->stateMachine = stateMachine;
	//this->stateMachine = 
	printf("IN NEW STATE ANGRY HAHHAHHAHAHHAHHAHHAHA!\n");
	emotion = 0;
	numberOfTurns = 0;
	ableToMovePiece = 0;
}

AIStateAngry::~AIStateAngry(void)
{

}

void AIStateAngry::doTurn(Player player)
{
	Sleep(1000);
	printf("I made the move there!!! yeSS!!!!!!!!!!!!!!!!!!!! HAHAHHAHAHHAHAH!!!! \n");
	numberOfTurns++;
	// Create a vector of rules that are of interest
	vector<TRule*> valid;
	TRule * curRule;

	// Keep track of the last rule fired. We will need it later on to check if you were attacked to reduce the weight.
	static int lastRuleFired = -1;

	// Flag the rules that matched
	for (int i = 0; i < GameData()->Rules.size(); i++)
	{
		curRule = &(GameData()->Rules.at(i));

		if (curRule->last == GameData()->Moves.at(0) && curRule->secondLast == GameData()->Moves.at(1) && 
			curRule->thirdLast == GameData()->Moves.at(2)) //what does this mean??
			valid.push_back(&(GameData()->Rules.at(i)));
	}

	// Decide which rule to use based on the valid list and given weights
	int ruleToFire = -1;
	int topWeight = 0;
	int highest = 0;
	int distance = 0;
	int movepos = -1;
	int potend = -1;
	int endpos = 0;
	int moveid = 0;
	int path = 0; //left or right (0 and less or 1 or above)

	for (int i = 0; i < valid.size(); i++)
	{
		if (ruleToFire == -1)
		{
			ruleToFire = valid.at(i)->rulenum;
			topWeight = valid.at(i)->weight;
		}
		else if (valid.at(i)->weight > topWeight)
		{
			ruleToFire = valid.at(i)->rulenum;
			topWeight = valid.at(i)->weight;
		}
	}

	bool moveUseful = 1; // assume the move was useful; tell us if it wasn't.
	TMove useMove = GameData()->Rules.at(ruleToFire).result;				//////USE MOVE IS THE RULE!!!!!!!!!!


	//find the active piece on the board.
	vector<int> possibleActiveMoves;

	for (int i = 0; i < MAX_GAME_POSITIONS; i++)
	{
		if (GameData()->board.IsPieceOnTop(player.piece, i))
			possibleActiveMoves.push_back(i);
	}

	vector<int> possibleStartMoves;

	for (int i = -1; i >= -GameData()->board.numstartstacks; i--)
	{
		if (GameData()->board.IsPieceOnTop(player.piece, i))
			possibleStartMoves.push_back(i);
	}





	/*	
	if (possibleActiveMoves.empty())
	{
		switch (useMove)
		{
			case TM_ATTACK:
			case TM_FORWARD:
				moveUseful = 0;
				useMove = TM_START;
			break;
		}
	}

	if (possibleStartMoves.empty())
	{
		switch (useMove)
		{
			case TM_START:
				moveUseful = 0;
				useMove = TM_FORWARD;
			break;
		}
	}
	// Actually perform the selected move
	*/
	int attacking = 1;
	//switch (useMove)
	//{
	//	case TM_ATTACK:
			// Make a piece attack a large stack
			// Useful if there is a large stack to jump on

			// Find a large stack that can be jumped on
			/*highest = -1; // reset
			for (int i = 0; i < (signed)possibleActiveMoves.size(); i++)
			{
				// Get numbers
				distance = GameData()->board.GetSizeOfStack(possibleActiveMoves.at(i)); //size of current stack
				potend = possibleActiveMoves.at(i) + distance;

				// Special case for left track
				if (possibleActiveMoves.at(i) <= 2 && potend > 2)
					potend += 3;

				if (GameData()->board.GetSizeOfStack(potend) >= highest)
				{
					highest = GameData()->board.GetSizeOfStack(potend);
					movepos = possibleActiveMoves.at(i);
				}
			}

			// Move piece
			GameData()->board.MovePiece(movepos, -1);

			if (highest < 2) // small stack -> not very useful
				moveUseful = 0;
			*/
			for (int i = 0; i < ((signed)possibleActiveMoves.size() + (signed)possibleStartMoves.size()); i++)
			{
				PIECE target;
				int goingToAttack = 0;
				int activeAble = possibleActiveMoves.size();
				int startAble = possibleStartMoves.size();
				if (activeAble != 0)
				{
					distance = GameData()->board.GetSizeOfStack(possibleActiveMoves.at(i)); //size of current stack
					potend = possibleActiveMoves.at(i) + distance;
					// Special case for left track
					if (possibleActiveMoves.at(i) <= 2 && potend > 2)
						potend += 3;
					target = GameData()->board.GetTopPiece(potend); //size of current stack	
					

					for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
					{
						if(target == possibleActiveMoves.at(j))
						{
							cout<<"\nFUCK THIS IS MY PIECE!!!!!\n"<<endl;
							//cout<<target<<endl;
							Sleep(1000);
						}
						else
						{
							cout<<"\nSOMEONE ELSES!\n"<<endl;
							goingToAttack++;
							break;
						}
					}
					if(goingToAttack == 1)
					{
						cout<<"ATTACKING FROM THE ACTIVE PIECES"<<endl;
						GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
						attacking = 0;
						Sleep(4000);
						break;
					}
				}
				else if(startAble !=0)
				{
					distance = GameData()->board.GetSizeOfStack(possibleStartMoves.at(i - possibleActiveMoves.size()));
					potend = distance;

					target = GameData()->board.GetTopPiece(potend); //size of current stack	
					for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
					{
						if(target == possibleActiveMoves.at(j))
						{
							cout<<"\nLEFT WAY ITS MINE!!!!!\n"<<endl;
							Sleep(1000);
						}
							//cout<<target<<endl;
						else
						{
							cout<<"\nSOMEONE ELSES ON LEFT!\n"<<endl;
							goingToAttack++;
							break;
						}
					}
					if(goingToAttack == 1)
					{
						cout<<"ATTACKING FROM THE STARTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT to left!!"<<endl;
						GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
						attacking = 0;
						Sleep(4000);
						break;
					}
					//potend += 3;
					if (attacking == 1)
					{
						potend += 3;
						for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
						{
							if(target == possibleActiveMoves.at(j))
							{
								cout<<"\nRIGHT WAY;s stuff is MINE!!!!!!!\n"<<endl;
								Sleep(1000);
							}
								//cout<<target<<endl;
							else
							{
								cout<<"\nSOMEONE ELSES on RIGHT WAY!\n"<<endl;
								goingToAttack++;
								break;
							}
						}
						if(goingToAttack == 1)
						{
							cout<<"I ATTTACKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK RIGHTfrom START!!!!!!!!!!!!!"<<endl;
							GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
							attacking = 0;
							Sleep(4000);
							break;
						}
					}
				}
				else
					cout<<"nothing to attack!!"<<endl;
			
		//break;
				/*
		if(attacking == 1)
		switch(useMove)
		{
		case TM_ATTACK:
			for (int i = 0; i < ((signed)possibleActiveMoves.size() + (signed)possibleStartMoves.size()); i++)
			{
				PIECE target;
				int goingToAttack = 0;
				int activeAble = possibleActiveMoves.size();
				int startAble = possibleStartMoves.size();
				if (activeAble != 0)
				{
					distance = GameData()->board.GetSizeOfStack(possibleActiveMoves.at(i)); //size of current stack
					potend = possibleActiveMoves.at(i) + distance;
					// Special case for left track
					if (possibleActiveMoves.at(i) <= 2 && potend > 2)
						potend += 3;
					target = GameData()->board.GetTopPiece(potend); //size of current stack	
					

					for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
					{
						if(target == possibleActiveMoves.at(j))
							cout<<"\nFUCK THIS IS MY PIECE!!!!!\n"<<endl;
							//cout<<target<<endl;
						else
						{
							cout<<"\nSOMEONE ELSES!\n"<<endl;
							goingToAttack++;
							break;
						}
					}
					if(goingToAttack == 1)
					{
						cout<<"I ATTTACKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK"<<endl;
						GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
						attacking = 0;
						Sleep(4000);
						break;
					}
				}
				else if(startAble !=0)
				{
					distance = GameData()->board.GetSizeOfStack(possibleStartMoves.at(i - possibleActiveMoves.size()));
					potend = distance;

					target = GameData()->board.GetTopPiece(potend); //size of current stack	
					for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
					{
						if(target == possibleActiveMoves.at(j))
							cout<<"\nFUCK THIS IS MY PIECE!!!!!\n"<<endl;
							//cout<<target<<endl;
						else
						{
							cout<<"\nSOMEONE ELSES!\n"<<endl;
							goingToAttack++;
							break;
						}
					}
					if(goingToAttack == 1)
					{
						cout<<"I ATTTACKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK"<<endl;
						GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
						attacking = 0;
						Sleep(4000);
						break;
					}
					//potend += 3;
					if (attacking !=0)
					{
						potend += 3;
						for (int j = 0; j < (signed)possibleActiveMoves.size(); j++)
						{
							if(target == possibleActiveMoves.at(j))
								cout<<"\nFUCK THIS IS MY PIECE!!!!!\n"<<endl;
								//cout<<target<<endl;
							else
							{
								cout<<"\nSOMEONE ELSES!\n"<<endl;
								goingToAttack++;
								break;
							}
						}
						if(goingToAttack == 1)
						{
							cout<<"I ATTTACKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK"<<endl;
							GameData()->board.MovePiece(possibleActiveMoves.at(i), -1);
							attacking = 0;
							Sleep(4000);
							break;
						}
					}
				}
				else
					break;
			}
			
			break;
		case TM_FORWARD:
			// Move a piece forward by the stack size
			// Useful if the lap was significant

			// Seek the farthest move ahead
			distance = -1; //reset

			for (int i = 0; i < (signed)possibleActiveMoves.size(); i++)
			{
				// Get numbers
				static int tempdist;
				tempdist = GameData()->board.GetSizeOfStack(possibleActiveMoves.at(i));

				// Can hit Lotus?
				if (i + tempdist == LOTUS_TRAMPOLINE)
					tempdist *= 2;

				if (tempdist >= distance)
				{
					distance = GameData()->board.GetSizeOfStack(possibleActiveMoves.at(i));
					movepos = possibleActiveMoves.at(i);
				}
			}

			// Move the piece
			if (distance < 3) // not particularly wortwhile
				moveUseful = 0;

			GameData()->board.MovePiece(movepos, -1);

		break;

		case TM_START:
			// Take out a piece from the start if possible
			// Otherwise perform a random action...
			// Useful if the start piece can jump on top of another stack
			// Not useful if a random move needed to be performed

			movepos = possibleStartMoves.at(0);

			// Decide on a path by taking the one with fewer pieces
			for (int i = 0; i < 7; i++)
			{
				if (i <= 2)
					path -= GameData()->board.GetSizeOfStack(i);
				else
					path += GameData()->board.GetSizeOfStack(i);
			}

			path *= -1; //flip it so you go down the path with fewer pieces

			// If there's only one stack left you must select from there
			if (possibleStartMoves.size() == 1)
				movepos = possibleStartMoves.at(0);

			// Go for the first stack that can jump on a piece (otherwise assume the above ^)
			for (int i = 0; i < possibleStartMoves.size(); i++)
			{
				static int tempend = -1;
				static PIECE temppc;

				if (path <= 0)
				{
					if (GameData()->board.GetSizeOfStack(possibleStartMoves.at(i)) == 4)
						tempend = 6;
					else
						tempend = GameData()->board.GetSizeOfStack(possibleStartMoves.at(i)) - 1;
				}
				else
					tempend = GameData()->board.GetSizeOfStack(possibleStartMoves.at(i)) + 2;

				temppc = GameData()->board.GetTopPiece(tempend);

				if (temppc != player.piece && temppc != PIECE_BAD)
				{
					moveid = i;
					movepos = possibleStartMoves.at(i);
					break;
				}
			}

			// Move the piece
			if (path <= 0) //left path
			{
				if (GameData()->board.GetSizeOfStack(possibleStartMoves.at(moveid)) == 4)
					endpos = 6;
				else
					endpos = GameData()->board.GetSizeOfStack(possibleStartMoves.at(moveid)) - 1;
			}
			else
				endpos = GameData()->board.GetSizeOfStack(possibleStartMoves.at(moveid)) + 2;

			// Update and and change your state
			GameData()->board.MovePiece(movepos, endpos);

		break;

		default:
			// Do nothing; your move was useless
			moveUseful = 0;
		break;
	}



	//this->stateMachine->setState(ST_REGULAR);

	
	//break;*/
}
}

void AIStateAngry::onBoardChange()
{
	printf("target AI got the Board Update I GOT THE UPDATE !!!! AND I'm ANGRY!!!!!!!!!!!!!\n");
	//if AI got attack!!?!? 
	vector<int> possibleStartMoves;
	for (int i = -1; i >= -GameData()->board.numstartstacks; i--)
	{
		if (GameData()->board.IsPieceOnTop(this->stateMachine->player->piece, i))
		{
			possibleStartMoves.push_back(i);
		}
	}

	
	vector<int> possibleActiveMoves;
	for (int i = 0; i < MAX_GAME_POSITIONS; i++)
	{
		if (GameData()->board.IsPieceOnTop(this->stateMachine->player->piece, i))
		{

			possibleActiveMoves.push_back(i);
		}
	}
	//if (!(possibleStartMoves.empty()))
	//	ableToMovePiece++;
	if (possibleActiveMoves.size() <= ableToMovePiece)
		emotion++;
	//else
	//	emotion--;
	

	cout<<emotion<<endl;
	cout<<possibleActiveMoves.size()<<endl;
	cout<<numberOfTurns<<endl;
	//cout<<typeid(this).name()<<endl;
	//if (emotion == 1)
	//	this->stateMachine->setState(ST_VENGEFUL);
	if (numberOfTurns > 4)
		this->stateMachine->setState(ST_REGULAR);
	
}
