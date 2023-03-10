#include"rubiks_cube_solver.h"
int co_to_index(int co[8]) {
	int index = 0;
	int cardinal = 1;
	for (int i = 0; i < 7; i++) {
		index += co[i] * cardinal;
		cardinal *= 3;
	}
	return index;
}
void index_to_co(int co[8], int index) {
	int sum = 0;
	for (int i = 0; i < 7; i++) {
		co[i] = index % 3;
		index /= 3;
		sum += co[i];
	}
	co[7] = (3 - sum % 3) % 3;//kore!!
}
int eo_to_index(int eo[12]) {
	int index = 0;
	int cardinal = 1;
	for (int i = 0; i < 11; i++) {
		index += eo[i] * cardinal;
		cardinal *= 2;
	}
	return index;
}
void index_to_eo(int eo[12], int index) {
	int sum = 0;
	for (int i = 0; i < 11; i++) {
		eo[i] = index % 2;
		index /= 2;
		sum += eo[i];
	}
	eo[11] = (2 - sum % 2) % 2;
}
int nCk(int n, int k) {
	if (k > n) {
		return 0;
	}
	else if ((k == 0) || (n == k)) {
		return 1;
	}
	else {
		return nCk(n - 1, k) + nCk(n - 1, k - 1);
	}
}
int e_con_to_index(int ep[12]) {
	int rest[12] = { 0 };
	for (int i = 0; i < 12; i++) {
		if ((0 <= ep[i]) && (ep[i] <= 3)) {
			rest[i] = 1;
		}
		else {
			rest[i] = 0;
		}
	}
	int index = 0;
	int r = 4;
	for (int i = 11; i >= 0; i--) {
		if (rest[i]) {
			index += nCk(i, r);
			r--;
		}
	}
	return index;
}
void index_to_e_con(int ep[12], int index) {
	int r = 4;
	int rest = 0;
	for (int i = 11; i >= 0; i--) {
		if (index >= (rest = nCk(i, r))) {
			ep[i] = 1;
			index -= rest;
			r--;
		}
	}
}
int cp_to_index(int cp[8]) {
	int index = 0;
	for (int i = 0; i < 8; i++) {
		index *= (8 - i);
		for (int j = i + 1; j < 8; j++) {
			if (cp[i] > cp[j]) {
				index++;
			}
		}
	}
	return index;
}
void index_to_cp(int cp[8], int index) {
	for (int i = 6; i >= 0; i--) {
		cp[i] = index % (8 - i);
		index /= (8 - i);
		for (int j = i + 1; j < 8; j++) {
			if (cp[i] <= cp[j]) {
				cp[j]++;
			}
		}
	}
}
int ud_ep_to_index(int ep[12]) {
	int index = 0;
	for (int i = 0 + 4; i < 8 + 4; i++) {
		index *= (8 + 4 - i);
		for (int j = i + 1; j < 8 + 4; j++) {
			if (ep[i] > ep[j]) {
				index++;
			}
		}
	}
	return index;
}
void index_to_ud_ep(int ep[12], int index) {
	for (int i = 6 + 4; i >= 0 + 4; i--) {
		ep[i] = index % (8 + 4 - i);
		index /= (8 + 4 - i);
		for (int j = i + 1; j < 8 + 4; j++) {
			if (ep[i] <= ep[j]) {
				ep[j]++;
			}
		}
	}
}
int e_ep_to_index(int ep[12]) {
	int index = 0;
	for (int i = 0; i < 4; i++) {
		index *= (4 - i);
		for (int j = i + 1; j < 4; j++) {
			if (ep[i] > ep[j]) {
				index++;
			}
		}
	}
	return index;
}
void index_to_e_ep(int ep[12], int index) {
	for (int i = 2; i >= 0; i--) {
		ep[i] = index % (4 - i);
		index /= (4 - i);
		for (int j = i + 1; j < 4; j++) {
			if (ep[i] <= ep[j]) {
				ep[j]++;
			}
		}
	}
}
