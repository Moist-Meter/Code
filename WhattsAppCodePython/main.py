# Download the helper library from https://www.twilio.com/docs/python/install
from twilio.rest import Client
import serial
import time
ser = serial.Serial('COM5', 9600)
limitMax = float(60)
limitMin = float(20)

# Your Account Sid and Auth Token from twilio.com/console
account_sid = 'ACe85a940845c258d6517546d842688788'
auth_token = '0daa61cc806283191117e72c0323b19e'
client = Client(account_sid, auth_token)


while True:
    while ser.inWaiting():
        moist = ser.readline().decode()
        messageToMax = "Attention!!! Too Moist, above 60%: " + str(moist) + "%."
        messageToMin = "Attention!!! Too Dry, below 20%: " + str(moist) + "%."

        reading = float(moist)
        if reading > limitMax:
            message = client.messages.create(
                              body=messageToMax,
                              from_='whatsapp:+14155238886',
                              to='whatsapp:+353871635307'
                          )
        elif reading < limitMin:
            message = client.messages.create(
                body=messageToMin,
                from_='whatsapp:+14155238886',
                to='whatsapp:+353871635307'
            )
        else:
            time.sleep(10)

print(message.sid)