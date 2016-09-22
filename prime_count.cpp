// Count prime numbers up to N
//
// To initialize, call init_prime_count() first.
// Function count_primes(N) will compute the number of prime numbers lower than
// or equal to N.
//
// Constants to configure:
// - MAX is the maximal value of sqrt(N) + 2

bool prime[MAX];
int prec[MAX];

llint rec(llint N, int K) {
  if (N <= 1 || K < 0) return 0;
  if (N <= P[K]) return N-1;
  if (N < MAX && llint(P[K])*P[K] > N) return N-1 - prec[N] + prec[P[K]];

  const int LIM = 250;
  static int memo[LIM*LIM][LIM];

  bool ok = N < LIM*LIM;
  if (ok && memo[N][K]) return memo[N][K];

  llint ret = N/P[K] - rec(N/P[K], K-1) + rec(N, K-1);

  if (ok) memo[N][K] = ret;
  return ret;
}

llint count_primes(llint N) {
  if (N < MAX) return prec[N];
  int K = prec[(int)sqrt(N) + 1];
  return N-1 - rec(N, K) + prec[P[K]];
}

void init_prime_count() {
  prime[2] = true;
  for (int i = 3; i < MAX; i += 2) prime[i] = true;

  for (int i = 3; i*i < MAX; i += 2)
    if (prime[i])
      for (int j = i*i; j < MAX; j += i+i)
        prime[j] = false;

  FOR(i, 1, MAX) prec[i] = prec[i-1] + prime[i];
}
