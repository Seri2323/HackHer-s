import os
import requests
from openai import OpenAI

# Load the environment variables


# AI functionality class 
class AI:

    def __init__(self, SAVE_FOLDER):
        self.SAVE_FOLDER = SAVE_FOLDER
        self.client = OpenAI(api_key = open("../OPEN_AI_API_KEY.txt", "r").read().strip())
        try:
            os.makedirs(SAVE_FOLDER, exist_ok = True)
        except OSError as e:
            print(f"Error creating save folder {SAVE_FOLDER} : {e}")




    def generateImage(self, PROMPT, NAME, COUNT, SIZE):
        response = self.client.images.generate(
            prompt = PROMPT, 
            n = COUNT, 
            size = SIZE)

        imageURL = response.data[0].url
        imagePath = os.path.join(self.SAVE_FOLDER, NAME)

        response = requests.get(imageURL)
        if response.status_code == 200:
            with open(imagePath, 'wb') as image:
                image.write(response.content)





    def generateDescription(self, PROMPT):
        response = self.client.completions.create(
            model = "gpt-3.5-turbo", 
            prompt = PROMPT, 
            max_tokens = 100)
        return response.choices[0].text.strip()



    def generateImagePrompt(self, DESCRIPTION):
        response = self.client.completions.create(
            model="gpt-3.5-turbo",
            prompt=f"Create a prompt for DALL·E to generate an image of the following clothing item: {DESCRIPTION}", 
            max_tokens=50)
        return response.choices[0].text.strip()



    def generateName(self, DESCRIPTION):
        response = self.client.completions.create(
            model="gpt-3.5-turbo",
            prompt=f"Create a trendy short, Gen-Z style name for this clothing item: {DESCRIPTION}", 
            max_tokens=50)
        return response.choices[0].text.strip()


    def generateGenzBio(self, DESCRIPTION):
        response = self.client.completions.create(
            model="gpt-3.5-turbo",
            prompt=f"Write a trendy, Gen-Z style bio for this clothing item, suitable for a Tinder-like shopping app. The bio should be 3 to 4 phrases long and no more than 200 words: {DESCRIPTION}", 
            max_tokens=100)
        return response.choices[0].text.strip()



    def runAll(self, PROMPT, NUMBER = 4):
        description = self.generateDescription(PROMPT)
        imagePrompt = self.generateImagePrompt(description)
        genzBio     = self. generateGenzBio(description)
        name        = self.generateName(description)

        self.generateImage(self, imagePrompt, f"Stuti_Puti_{NUMBER}.png", 1, "1024x1024")
        return [genzBio, name, f"Stuti_Puti_{NUMBER}.png"];

