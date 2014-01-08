logparse
========

一个C版本的高效的nginx/apache访问日志分析库

日志格式
-------------------------------------------
日志为nginx输出日志,需要做通配处理

::

    124.14.12.152:80 124.14.12.153 [08/Jan/2014:11:40:00 +0800] "GET /m3u8/cctv6/desc.m3u8?tag=live&video_type=m3u8&stream_id=cctv6&useloc=0&mslice=3&path=124.193.120.75,124.193.120.85&geo=CN-9-117-11&cips=101.45.236.123&tmn=1389150596&pnl=346,9968,224&ext=m3u8&sign=live_tv&m3u8_args=dGFnPWxpdmUmdmlkZW9fdHlwZT1tM3U4JnN0cmVhbV9pZD1jY3R2NiZ1c2Vsb2M9MCZtc2xpY2U9MyZwYXRoPTEyNC4xNC4xMi4xNTIsMTI0LjE5My4xMjAuNzUsMTI0LjE5My4xMjAuODUmZ2VvPUNOLTktMTE3LTExJmNpcHM9MTAxLjQ1LjIzNi4xMjMmdG1uPTEzODkxNTA1OTYmcG5sPTM0Niw5OTY4LDIyNCZleHQ9bTN1OCZzaWduPWxpdmVfdHY= HTTP/1.0" 200 812 0.058 "-" "owninneragent" "-" 124.14.12.152 MISS 32222 -
    124.14.12.152:80 101.44.149.226 [08/Jan/2014:11:39:59 +0800] "GET /video/ts-88800-8066-0-0/49/13/56/letv-uts/9231582-avc-250151-aac-32000-1393000-49516911-f621698274df760c55c5b234d2897107-1387092958692.mp4?proxy=2071812451,2007470985&tag=-&platid=3&tss=ios&splatid=304&playid=0&b=284&bf=27&nlh=3072" 200 319224 0.000 "-" "AppleCoreMedia/1.0.0.11B554a (iPad; U; CPU OS 7_0_4 like Mac OS X; zh_cn)" "-" 124.14.12.152 HIT 31961 -
    124.14.12.152:80 124.14.58.123 [08/Jan/2014:11:40:00 +0800] "GET /42/16/57/letv-uts/8654810-avc-489362-aac-31586-1470010-99030049-c387fab18515922517359dc47fc9eff3-1385250196999.letv?crypt=10aa7f2e185&b=538&nlh=3072&nlt=45&bf=28&gn=346&p2p=1&video_type=flv&opck=1&check=0&tm=1389584400&key=d9916a3207bedf2ce33845ac0fa4df37&proxy=2071812444,2007470978&cips=124.14.58.123&geo=CN-9-0-11&lgn=letv&mmsid=3487412&platid=1&splatid=101&playid=0&tss=no&tag=letv&sign=dm456&rateid=1000&rstart=41156608&rend=42598399 HTTP/1.1" 200 1000430 0.477 "http://player.letvcdn.com/p/201212/19/11/newplayer/LetvPlayer.swf?typeFrom=dm456&v_list=35&id=2185980&autoplay=1&typeFrom=dm456&isPlayerAd=0" "Mozilla/4.0 (compatible; MSIE 8.0; YYGameAll_1.2.161288.80; Windows NT 5.1; Trident/4.0; QQDownload 718; .NET CLR 2.0.50727)" "-" 124.14.12.152 HIT 31767 bytes=41156608-42598399
    124.14.12.152:80 115.174.146.105 [08/Jan/2014:11:40:00 +0800] "GET /31/28/109/letv-uts/7121522-AVC-549351-AAC-32000-2694960-197001423-6826a6654e9169d417b2b54036c33a62-1381048744405.mp4?crypt=53aa7f2e199&b=584&nlh=3072&nlt=45&bf=27&gn=346&p2p=1&video_type=mp4&opck=1&check=0&tm=1389157200&key=dee6112f66f2d26a68b6867bf1fbc923&proxy=3702889256,2007487114&cips=115.174.146.105&geo=CN-9-0-11&lgn=letv&mmsid=3161861&platid=3&splatid=302&playid=0&tss=no&sign=mb&dname=mobile&tag=mobile&vtype=play HTTP/1.1" 206 226516 0.032 "-" "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2.3) Gecko/20100401" "-" 124.14.12.152 HIT 31770 bytes=65667141-131334282
    124.14.12.152:80 180.88.7.214 [08/Jan/2014:11:40:00 +0800] "GET /leflv/channel_1_pc/2014010811/1389152343_7520_1329450.dat?tag=live&video_type=xml&stream_id=channel_1_pc&useloc=0&mslice=3&path=124.14.12.145,124.193.120.68,124.193.120.82&geo=CN-19-246-11&cips=180.88.7.214&tmn=1389152126&pnl=346,9968,224&ext=xml&sign=live_web&scheme=rtmp&termid=1&pay=0&ostype=Windows%208&hwtype=un&platid=10&splatid=1001&playid=1&tm=1389238525&key=3bb91c8b38d7dcaa3e86f6ee35f24966&rdm=1389152406294 HTTP/1.1" 200 1329450 0.421 "http://player.hz.letv.com/live.swf" "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.89 Safari/537.1" "-" 124.14.12.152 HIT 31761 -
    124.14.12.152:80 49.221.238.11 [08/Jan/2014:11:40:00 +0800] "GET /m3u8/jiangsu/2014010811/1389152381_6640_783208.ts?tag=live&video_type=m3u8&stream_id=jiangsu&useloc=0&mslice=3&path=124.14.12.154,124.193.120.77,124.193.120.86&geo=CN-9-0-11&cips=49.221.238.11&tmn=1389148479&pnl=346,9968,224&ext=m3u8&sign=live_tv HTTP/1.1" 200 783208 0.063 "-" "RealtekVOD/1.0.0 (Linux)" "-" 124.14.12.152 MISS 32010 -


解析后
-------------------------------------
解析为 `hashtable` 或者结构体
