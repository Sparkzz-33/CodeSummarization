import json
import os
import subprocess
from urllib.request import urlopen
# os.system("curl https://api.github.com/repositories > repo.json")
f = open("repoLinkC.txt", "w", encoding="utf-8")
f.close()
f = open("repoLinkC.txt", "a", encoding="utf-8")
datasetsGenerated = 0
for i in range(34):
    repo = subprocess.run(['curl', '-u', 'naxs-me-code:1!repository',"https://api.github.com/search/repositories?sort=stars&order=desc&q=language:cpp&page="+str(i+1)], stdout=subprocess.PIPE)
    temp = repo.stdout.decode("utf-8")
    repoJson = []
    repoJson = json.loads(temp)
    repoArr = repoJson["items"]
    for r in repoArr:
        link = r["html_url"]
        f.write(link+"\n")
        if(datasetsGenerated<10):
            os.system("g++ -std=c++11 script.cpp")
            os.system("./a.out " + link + ".git ./database")
            datasetsGenerated+=1
    
f.close()
# print(repoArr[0])
# f = open("demofile2.txt", "w")
# f.write(temp)
# f.close()
# repoCount = 1000
# currRepo = 0
# while(currRepo<repoCount):
#     f = open('repo.json',)
#     data = json.load(f) 
#     lastRepo = data[-1]["id"]
#     os.system("curl https://api.github.com/repositories?since=" + str(lastRepo) + " >> repo.json")
#     currRepo = len(data)