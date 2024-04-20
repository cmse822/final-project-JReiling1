import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import warnings

warnings.filterwarnings("ignore")

def create_df(csv_link):
    df = pd.read_csv(csv_link, low_memory=False)
    print(df)

    df_10 = pd.DataFrame(columns=df.columns)
    df_100 = pd.DataFrame(columns=df.columns)
    df_1000 = pd.DataFrame(columns=df.columns)
    df_2000 = pd.DataFrame(columns=df.columns)

    for index, row in df.iterrows():
        if row[0] == 10:
            df_10 = pd.concat([df_10, pd.DataFrame([row])], ignore_index = True)
        elif row[0] == 100:
            df_100 = pd.concat([df_100, pd.DataFrame([row])], ignore_index = True)
        elif row[0] == 1000:
            df_1000 = pd.concat([df_1000, pd.DataFrame([row])], ignore_index = True)
        else:
            df_2000 = pd.concat([df_2000, pd.DataFrame([row])], ignore_index = True)

    print(df_10)
    print(df_100)
    print(df_1000)
    print(df_2000)

    return df_10, df_100, df_1000, df_2000
    

def create_plot(df, N, parallel_name):
    # Create a plot for df_20
    plt.figure(figsize = (10,5))
    plt.scatter(df[' Num Threads'], df[' Runtime'], label='Number of threads vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Number of Threads')
    plt.ylabel('Runtime (seconds)')
    plt.title(f"{parallel_name} Num Threads vs Runtime for N= {N}")
    plt.savefig(f"results/{parallel_name}/NumThreadsVsRuntimeN={N}.png")
    plt.legend(loc='upper right',)
    plt.ylim(min(df[' Runtime']), max(df[' Runtime']))
    plt.grid(True)
    plt.show()

def create_serial_plot(df, parallel_name):
    # Create a plot for df_20
    plt.figure(figsize = (10,5))
    plt.scatter(df['Num Verticies'], df[' Runtime'], label='Number of graph vs runtime', linestyle='-', linewidth=1, color='blue')
    plt.xlabel('Num Verticies')
    plt.ylabel('Runtime (seconds)')
    plt.title(f"{parallel_name} Num Verticies vs Runtime")
    plt.savefig(f"results/{parallel_name}/NumThreadsVsRuntime.png")
    plt.legend(loc='upper right',)
    plt.ylim(min(df[' Runtime']), max(df[' Runtime']))
    plt.grid(True)
    plt.show()

def main(): 
    # Read csv and create plot for openMP
    dijkstra_openMP_csv = 'dijkstra_openMP.csv'
    open_mp = "OpenMP"
    df_10, df_100, df_1000, df_2000 = create_df(dijkstra_openMP_csv)

    create_plot(df_10, 10, open_mp)
    create_plot(df_100, 100, open_mp)
    create_plot(df_1000, 1000, open_mp)

    # Read csv and create plot for MPI
    dijkstra_MPI_csv = 'dijkstra_MPI.csv'
    MPI_name = "MPI"
    df_10, df_100, df_1000, df_2000 = create_df(dijkstra_MPI_csv)

    create_plot(df_10, 10, MPI_name)
    create_plot(df_100, 100, MPI_name)
    create_plot(df_1000, 1000, MPI_name)

    # Read csv and create plot for serial
    dijkstra_serial_csv = 'dijkstra_serial.csv'
    serial_name = "Serial"
    df_serial = pd.read_csv(dijkstra_serial_csv, low_memory=False)

    create_serial_plot(df_serial, serial_name)



main()