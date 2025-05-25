#include <stdio.h>
#include "nbtrees.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    for (int i = 1; i <= jml_maks; i++) {
        X[i].info = '\0';
        X[i].ps_fs = 0;
        X[i].ps_nb = 0;
        X[i].ps_pr = 0;
    }

    for (int i = 1; i <= Jml_Node; i++) {
        printf("Masukkan info node ke-%d: ", i);
        scanf(" %c", &X[i].info);

        if (i == 1) continue; // root

        int parent;
        printf("Masukkan parent untuk node '%c': ", X[i].info);
        scanf("%d", &parent);

        X[i].ps_pr = parent;

        if (X[parent].ps_fs == 0) {
            X[parent].ps_fs = i;
        } else {
            int sibling = X[parent].ps_fs;
            while (X[sibling].ps_nb != 0) {
                sibling = X[sibling].ps_nb;
            }
            X[sibling].ps_nb = i;
        }
    }
}

boolean IsEmpty(Isi_Tree P) {
    return P[1].info == '\0';
}

/*** TRAVERSAL ***/

void PreOrder(Isi_Tree P) {
    int stack[jml_maks];
    int top = -1;

    if (IsEmpty(P)) return;

    stack[++top] = 1;

    while (top >= 0) {
        int idx = stack[top--];
        printf("%c ", P[idx].info);

        // Push siblings in reverse order
        int child = P[idx].ps_fs;
        int temp[jml_maks], t = 0;

        while (child != 0) {
            temp[t++] = child;
            child = P[child].ps_nb;
        }

        for (int i = t - 1; i >= 0; i--) {
            stack[++top] = temp[i];
        }
    }
}

void InOrder(Isi_Tree P) {
    void inorderRecursive(int idx) {
        if (idx == 0 || P[idx].info == '\0') return;

        int fs = P[idx].ps_fs;
        if (fs != 0) {
            inorderRecursive(fs);
        }

        printf("%c ", P[idx].info);

        if (fs != 0) {
            int sibling = P[fs].ps_nb;
            while (sibling != 0) {
                inorderRecursive(sibling);
                sibling = P[sibling].ps_nb;
            }
        }
    }
    inorderRecursive(1);
}

void PostOrder(Isi_Tree P) {
    void postorderRecursive(int idx) {
        if (idx == 0 || P[idx].info == '\0') return;

        int child = P[idx].ps_fs;
        while (child != 0) {
            postorderRecursive(child);
            child = P[child].ps_nb;
        }

        printf("%c ", P[idx].info);
    }
    postorderRecursive(1);
}

void Level_order(Isi_Tree X, int Maks_node) {
    for (int i = 1; i <= Maks_node; i++) {
        if (X[i].info != '\0') {
            printf("%c ", X[i].info);
        }
    }
}

void PrintTree(Isi_Tree P) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') {
            printf("Node %d: %c, FS=%d, NB=%d, PR=%d\n",
                   i, P[i].info, P[i].ps_fs, P[i].ps_nb, P[i].ps_pr);
        }
    }
}

/*** SEARCHING & ANALYSIS ***/

boolean Search(Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) return 1;
    }
    return 0;
}

int nbElmt(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') count++;
    }
    return count;
}

int nbDaun(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0' && P[i].ps_fs == 0) {
            count++;
        }
    }
    return count;
}

int Level(Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info == X) {
            int level = 0;
            int idx = i;
            while (P[idx].ps_pr != 0) {
                idx = P[idx].ps_pr;
                level++;
            }
            return level;
        }
    }
    return -1;
}

int Depth(Isi_Tree P) {
    int depthRecursive(int idx) {
        if (idx == 0 || P[idx].info == '\0') return 0;

        int maxD = 0;
        int child = P[idx].ps_fs;
        while (child != 0) {
            int d = depthRecursive(child);
            if (d > maxD) maxD = d;
            child = P[child].ps_nb;
        }
        return maxD + 1;
    }
    if (IsEmpty(P)) return 0;
    return depthRecursive(1);
}

int Max(infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}
