import requests
import json

api = "f25e4e03093c02ed3c52668dd29ebc4e"

f = open("storage/info.dat", "r")
city = f.readline()
f.close()

url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&units=metric&appid={api}"


f = open("storage/info.dat", "w")
try:
    data = requests.get(url).text
    result = json.loads(data)
except:
    f.write("12029")
    f.close()
    quit()

try:
    
    f.write (f'{result["name"]}\n') # City Name
    f.write(f'{result["sys"]["country"]}\n') # Country
    f.write(f'{float(round(result["main"]["temp"]))}C\n') # Tempratur
    f.write(f'{result["main"]["feels_like"]}C\n') # Feels Like
    f.write(f'{result["weather"][0]["main"]}\n') # Weather
    f.write(f'{result["coord"]["lat"]}\n') # Latitude
    f.write(f'{result["coord"]["lon"]}\n') # Longitude
    f.write(f'{result["main"]["pressure"]}hPa\n') # Pressure [hecto Pascal (100)]
    f.write(f'{result["main"]["humidity"]}%\n') # Humidity
    f.write(f'{result["visibility"]/1000} km') # Visibility
    
except:
    f.write("404")
f.close()