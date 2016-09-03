// reader-writer FIFO lock -- type 1

typedef volatile struct {
  uint16_t bits[1];
} RWLock1;

#define WAFLAG 0x1
#define RDINCR 0x2

void writeLock1 (RWLock1 *lock);
void writeUnlock1 (RWLock1 *lock);
void readLock1 (RWLock1 *lock);
void readUnlock1 (RWLock1 *lock);

// reader-writer mutex lock (Neither FIFO nor Fair) -- type 2

typedef volatile union {
#ifdef FUTEX
  struct {
	uint16_t lock[1];
	uint16_t futex[1];
  };
  uint32_t bits[1];
#else
  char lock[1];
#endif
} Mutex;

void mutex_lock(Mutex* mutex);
void mutex_unlock(Mutex* mutex);

typedef struct {
  Mutex xcl[1];
  Mutex wrt[1];
  uint16_t readers[1];
} RWLock2;

void writeLock2 (RWLock2 *lock);
void writeUnlock2 (RWLock2 *lock);
void readLock2 (RWLock2 *lock);
void readUnlock2 (RWLock2 *lock);

// reader-writer Phase Fair/FIFO lock -- type 3

typedef volatile struct {
	uint16_t rin[1];
	uint16_t rout[1];
	uint16_t ticket[1];
	uint16_t serving[1];
} RWLock3;

#define PHID 0x1
#define PRES 0x2
#define MASK 0x3
#define RINC 0x4
