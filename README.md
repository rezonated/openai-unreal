# openai-unreal
OpenAI API wrapper and Blueprint Library for Unreal Engine.

Inspired by OpenAI API wrapper for Unity created by srcnalt: https://github.com/srcnalt/OpenAI-Unity

Tested in UE 5.0 and 5.1. launcher version

It covers almost all OpenAI available as of Jan 24th, 2023 - https://beta.openai.com/docs/api-reference/
- Completion
- Edits
- Files
- Fine-tune
- Image
- Moderations

## Getting started
Quick setup for this plugin:
- Create a UE project
- Grab the latest .zip file in the release page: https://github.com/rezonated/openai-unreal/releases
- In your root project folder, create a folder called "Plugins"
- Extract/copy the content of the .zip file to the newly created Plugins folder.
- Open your UE project and enable the plugin under "Open AI" category.

![Enable plugin](/Docs/enable_plugin.png)

- Restart your editor.
- Go to project settings, scroll ahead to Plugins > Open AI - Unreal category. 
- Fill out your API key and Organization ID that you can obtain by registering through OpenAI's website and generate API key.
- Paste your API key and Organization ID to respective fields

![Fill credentials](/Docs/fill_credentials.png)

- Done!

## Example usages
These are some of the examples for each API usage:
### Completion API - https://beta.openai.com/docs/api-reference/completions/create
Create a completion for a prompt of: "Give me a random name and greet me as a stranger." 

![Create completion example](/Docs/create_completions_example.png)

### Edits API - https://beta.openai.com/docs/api-reference/edits/create
Create an edit for an input of "What day of the wek is it?", and the instruction to "Fix typo."

![Create edit example](/Docs/create_edits_example.png)

### Embeddings API - https://beta.openai.com/docs/api-reference/embeddings/create
Create an embedding vector for an input of "The food delicious and the waiter..."

![Create embedding example](/Docs/create_embeddings_example.png)

### Moderations API - https://beta.openai.com/docs/api-reference/moderations/create
Classifies if the input violates the OpenAI's content violation policy.

![Create_moderation_example](/Docs/create_moderations_example.png)

### Files and Fine-tune API - https://beta.openai.com/docs/api-reference/files, https://beta.openai.com/docs/api-reference/fine-tunes
Uploads a .jsonl file containing training examples that will be used for creating fine-tune purposes.

![Upload file and create fine tunes example](/Docs/upload_file_and_create_fine_tunes_example.png)

### Images API - https://beta.openai.com/docs/api-reference/images
You can choose to receive the response in either URL or Base64 JSON format.

- Create an image edit using base image and a mask image with a prompt of "Add bird", and then convert it into a Texture2D.

![Create image edits URL example](/Docs/create_image_edits_url_example.png)

- Create an image variation using base image.

![Create image variation base64 example](/Docs/create_image_variations_base64_example.png)

## Example maps
This plugin ships with two example maps of implementations that make use of completion and images API. It can be found under plugin content folder. 

**Make sure you enable the view of the plugin content.**

![Implementations example maps](/Docs/implementation_example_maps.png)

## Test files
Test files can be found under {Your project directory}/Plugins/UnrealOpenAI/Content/Test/

It consists of example files for testing:
- pool_empty.png -> for base image
- pool_mask.png -> for image mask
- training.jsonl -> containing training data for fine-tuning
