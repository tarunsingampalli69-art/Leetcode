class Solution {
public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> halfCnt(26, 0);
        string mid = "";
        int halfLen = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] & 1) mid.push_back(char('a' + i));
            halfCnt[i] = freq[i] / 2;
            halfLen += halfCnt[i];
        }

        // Smallest prime factor
        vector<int> spf(halfLen + 1);
        for (int i = 0; i <= halfLen; i++) spf[i] = i;

        for (int i = 2; i * i <= halfLen; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= halfLen; j += i)
                    if (spf[j] == j)
                        spf[j] = i;
            }
        }

        vector<int> primes;
        vector<int> id(halfLen + 1, -1);

        for (int i = 2; i <= halfLen; i++) {
            if (spf[i] == i) {
                id[i] = primes.size();
                primes.push_back(i);
            }
        }

        int P = primes.size();

        vector<vector<unsigned short>> factExp(
            halfLen + 1, vector<unsigned short>(P, 0));

        for (int i = 1; i <= halfLen; i++) {
            factExp[i] = factExp[i - 1];
            int x = i;
            while (x > 1) {
                int p = spf[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                factExp[i][id[p]] += cnt;
            }
        }

        auto countWays = [&](const vector<int>& cnt) -> long long {
            const long long LIM = 1000000LL;

            int total = 0;
            for (int x : cnt) total += x;

            long long ans = 1;

            for (int i = 0; i < P; i++) {
                int e = factExp[total][i];
                for (int x : cnt)
                    e -= factExp[x][i];

                long long base = primes[i];

                while (e > 0) {
                    if (e & 1) {
                        if (base > LIM || ans > LIM / base)
                            return LIM + 1;
                        ans *= base;
                    }
                    e >>= 1;
                    if (e) {
                        if (base > LIM || base > LIM / base)
                            base = LIM + 1;
                        else
                            base *= base;
                    }
                }

                if (ans > LIM)
                    return LIM + 1;
            }

            return ans;
        };

        if (countWays(halfCnt) < k)
            return "";

        string left = "";

        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (halfCnt[c] == 0)
                    continue;

                halfCnt[c]--;

                long long ways = countWays(halfCnt);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                halfCnt[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};