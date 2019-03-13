#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "HashSet.h"


#define MAGIC 123456
#define RE_HASH 13




struct HashSet  {
				size_t*   m_flags;		/*TODO  read ssize_t 	*/
				size_t*	  m_items;
				float     m_lood;
				size_t    m_hashSize;
				size_t    m_noItems;
				size_t    m_noInsert;
				size_t    m_noRehashOps;
				size_t    m_maxRehash;
				size_t    m_magic;
			/*	size_t    (*_hashfunction)(size_t);*/
				};


typedef enum {
				FREE =  0,
				FULL =  1,
				USED =  2
			 } FLAG;				
			 

static size_t Hashing(int _item);
static size_t Rehashing(HashSet* _set, int _item);
static int HashGalFined(HashSet* _set, size_t _data, size_t* _rehashCounter);

				

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Create ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

HashSet* HashSetCreate(size_t _size, float _loadfactor,size_t (*_hashfunction)(size_t))
{
	HashSet* _set;
	
	if (_loadfactor > 1) return NULL;
	
	_set = (HashSet*) malloc(sizeof(HashSet*));
	if (!_set) return NULL;

	_set->m_items = malloc(_size*sizeof(int));
	if (!_set->m_items) return NULL;
	
	_set->m_flags = calloc(_size,sizeof(int));
	if (!_set->m_flags) return NULL ;
	
	_set->m_hashSize	= _size;
	_set->m_noItems		= 0;
	_set->m_noInsert    = 0;
	_set->m_noRehashOps = 0;
	_set->m_maxRehash   = 0;
	_set->m_lood		= _loadfactor;
	_set->m_magic		= MAGIC;

	return _set;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
void HashSetDestroy(HashSet* _set)
{
	if (!_set || _set->m_magic != MAGIC) return;

	free(_set->m_flags);
	free(_set->m_items);
	_set->m_magic = 15;
	free(_set);

}




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 

ADTErr HashSetInsert(HashSet* _set, size_t _data)
{
	size_t	loadfactor;	
	int		answer;
	size_t 	rehashCounter;
	
	if (!_set || _set->m_magic != MAGIC) return ERR_NOT_INITIALIZED;

	loadfactor = (size_t)((float)_set->m_hashSize * _set->m_lood);
	if (_set->m_noItems == loadfactor) return ERR_OVERFLOW;
	
	answer = HashGalFined( _set, _data, &rehashCounter);
	if (answer == -1 ) return ERR_EXIST;
	
	_set->m_items[answer] = _data;
	_set->m_flags[answer] = FULL;
	_set->m_noItems++ ;
	_set->m_noInsert++ ; 
	_set->m_noRehashOps = _set->m_noRehashOps + rehashCounter;
	if (_set->m_maxRehash < rehashCounter)
	{
		_set->m_maxRehash = rehashCounter;
	}
	
	return ERR_OK;
}
	

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Gal Fined  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 	

static int HashGalFined(HashSet* _set, size_t _data, size_t* _rehashCounter)
{
	size_t key;					/*if m_lood = 1 and _item not exsist - rum forever */
	int insertLocation;
	
	key = Hashing(_data);
	insertLocation = -1;
	
	while (_set->m_flags[key] != FREE)
	{	
		if (_set->m_flags[key] == FULL)
		{
			if (_set->m_items[key] == _data)
			{
				*_rehashCounter = (int)key;
				return -1;
			}
		}
		if (_set->m_flags[key] != USED && insertLocation == -1)
		{
			insertLocation = key;
		}
		key = Rehashing(_set, key);
		*_rehashCounter +=1;
	}
	if (insertLocation != -1)
	{
		return insertLocation;
	}
	return key;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
 
 
ADTErr HashSetRemove(HashSet* _set, size_t _data)
{	
	int answer;
	size_t removeLocation;
	
	if (!_set || _set->m_magic != MAGIC) return ERR_NOT_INITIALIZED;
	
	answer = HashGalFined( _set, _data, &removeLocation);
	if (answer == -1 ) return ERR_NOT_FOUND;
	
	
	_set->m_flags[removeLocation] = USED;
	_set->m_noItems-- ;
	return ERR_OK;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Contains ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
 
int HashSetContains(HashSet* _set, size_t _data)
{
	int		answer;				/*if m_lood = 1 and _item not exsist - rum forever */
	size_t	rehashCounter = 0;
	
	if (!_set || _set->m_magic != MAGIC)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	answer = HashGalFined(_set, _data, &rehashCounter);
	
	if (answer == -1) return ERR_EXIST;
	return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash SetNum Items ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 

size_t HashSetSize(const HashSet* _set)
{
	if (!_set || _set->m_magic != MAGIC) return ERR_NOT_INITIALIZED;
	
	return _set->m_noItems;
}
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Statistics ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 

ADTErr HashSetStatistics(const HashSet* _set, size_t *_maxCollisionsEver, float *_averageCollisions)
{
	if (!_set || _set->m_magic != MAGIC) return ERR_NOT_INITIALIZED;	
	
	*_maxCollisionsEver = _set->m_maxRehash;
	*_averageCollisions = _set->m_noRehashOps / _set->m_noItems;	
	
	return ERR_OK;
}
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set For Each ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
 
void HashSetForEach(const HashSet* _set, void (*_userFunction)(size_t _data))
{
	int i; 
	
	if (!_set || _set->m_magic != MAGIC || !_userFunction) return;

	for (i = _set->m_hashSize; i < _set->m_hashSize; i++)
	{
		if (_set->m_flags[i] == FULL)
		{
			_userFunction(_set->m_items[i]);
		}	
	}
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Max Rehash ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  

size_t HashSetMaxRehash(const HashSet* _set)
{
	if (!_set || _set->m_magic != MAGIC) return ERR_NOT_INITIALIZED;
	
	return _set->m_maxRehash;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hashing ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  

static size_t Hashing(int _item)
{
	return (_item%87); 
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Rehashing ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  

static size_t Rehashing(HashSet* _set, int _item)
{
	_item = _item + RE_HASH; 
	if (_item > _set->m_hashSize)
	{
		_item = _item % _set->m_hashSize;
	}
	return _item;
}








/* 	end of file  */
