import requests
import json

params = {
    'origin': "place_id:ChIJg4R3aQVFiEgRz8dmd7akBmE",  # Home for student, 31 Dunblane St, Glasgow G4 0HJ
    'destination': "place_id:ChIJJYXx7yBEiEgR76XjNOUkIrk",  # McDonald's, 101, 105 Sauchiehall St, Glasgow G2 3DD
    'mode': 'driving',
    'key': "AIzaSyDLnexJ5T_CKi1IHuzb4o7j1R1yJdIooF0"
}

response = requests.get(url='https://maps.googleapis.com/maps/api/directions/json', params=params)

print(response.text)

routes = json.loads(response.text)['routes'][0]['legs'][0]['steps']

f = open("direction.txt", "w")

for route in routes:
    if 'maneuver' in route:
        step = route['maneuver']
    else:
        step = 'go-straight'
    f.write(step+'\n')

    step = str(route['distance']['value'])
    f.write(step+'\n')

f.write('stop')
f.close()
