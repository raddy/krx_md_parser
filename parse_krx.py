import sys,os
from krx_parser import parse_pcap
import pandas as pd
import numpy as np
import time

def main(file_name,target_name):
    print 'Parsing %s ....' %file_name
    

    store = pd.HDFStore(target_name,'w') 
    
    df,exps,strikes,h1s = parse_pcap(file_name,'a',-1,2)

    store.append('pcap_data',df,data_columns=['symbol'],complevel=9,complib='blosc')
    if len(exps)>0:
        store.append('expiry_info',pd.DataFrame(exps.values(),index=exps.keys()))
    if len(strikes)>0:
        store.append('strike_info',pd.DataFrame(strikes.values(),index=strikes.keys()))
    if len(h1s)>0:
        store.append('h1s',h1s,data_columns=['id'],complevel=9,complib='blosc') 
    print store
    store.close()

def rtmain(file_name,target_name,start_time,end_time):
    print 'RT Parsing %s ....' %file_name
    
    store = pd.HDFStore(target_name,'w') 
    
    last_time = start_time
    stop_time = end_time
    one_minute = (1000000000*60)
    t= start_time

    while last_time<stop_time:
        ut = os.path.getmtime(file_name)
        ts = pd.Timestamp(ut*1e9).tz_localize('UTC').tz_convert('Asia/Seoul').replace(tzinfo=None).value
        print pd.Timestamp(t),pd.Timestamp(ts)
        df,exps,strikes,h1s = parse_pcap(file_name,'a',-1,2)

        last_time = df.index[-1]
        t  = last_time
    store.flush(fsync=True)
    time.sleep(6)
    print store
    store.close()

if __name__ == "__main__":
    if len(sys.argv) <= 2:
        sys.exit('Usage: %s pcap-path new-h5-path start_time<YYYYMMDDThhmmss.uuuuuu> end_time<YYYYMMDDThhmmss.uuuuuu> real-time-flag(0/1)' % sys.argv[0])

    if not os.path.exists(sys.argv[1]):
        sys.exit('ERROR: Raw Pcap file %s was not found!' % sys.argv[1])
    new_h5_path = sys.argv[2]
    
    if len(sys.argv)<4 or sys.argv[5] == '0': #not real time
        sys.exit(main(sys.argv[1],new_h5_path))
    if sys.argv[5] == '1': #real time!
        start_time_as_long = pd.Timestamp(sys.argv[3]).value
        end_time_as_long = pd.Timestamp(sys.argv[4]).value
        sys.exit(rtmain(sys.argv[1],new_h5_path,start_time_as_long,end_time_as_long))
