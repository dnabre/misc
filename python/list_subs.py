#
# The first half of this will get all your subreddits, and list them along with number of people in them
# sorted in decreasing number of members.
#
# The second half will cre  ate a multipage https://old.reddit.com/user/USERNAME/m/mysubreddits/ and populate
# it with your subreddits. Multipages are limited to 100 subreddits, so it will stop if hits that limit.
# It will delete that multipage if it already exists. If you just want to update to include existing subreddit
# remove the one line doing the delete
#
# you will have to create an app on reddit, to setup client_id/client_secret with permissinos to do stuff
# on  your account.

import praw
import argparse
import getpass


parser = argparse.ArgumentParser(description="Reddit client using PRAW")
parser.add_argument("--client_id", required=True, help="Reddit API client ID")
parser.add_argument("--client_secret", required=True, help="Reddit API client secret")
args = parser.parse_args()



# Prompt for Reddit credentials
username = input("Enter your Reddit username: ")
print(f"read username: {username}")
password = getpass.getpass("Enter your Reddit password (input hidden): ")
print(f"read password, {'*' * len(password)}")

# Initialize Reddit instance
reddit = praw.Reddit(
    client_id=args.client_id,
    client_secret=args.client_secret,
    username=username,
    password=password,
    user_agent=f'subreddit_counter by /u/{username}'
)
print(f"reddit praw instance created: {reddit}")

# Fetch and display subscribed subreddits
subreddits = list(reddit.user.subreddits(limit=None))
subreddits = sorted(subreddits, key=lambda s: s.subscribers, reverse=True)
for sub in subreddits:
    print(f"- {sub.display_name}, {sub.subscribers} follwers")
print(f"\nYou're subscribed to {len(subreddits)} subreddits:\n")



# Define multireddit name and owner
MULTI_NAME = "mysubreddits"
USERNAME = username

# Get your Redditor object
user = reddit.user.me()
print(f"praw user instance created: {user}")
# Fetch current subscriptions
# subs = list(user.subreddits(limit=None))
subs = subreddits
sub_names = [sub.display_name for sub in subs]

print(f"Found {len(sub_names)} subscribed subreddits.")

# Check if multireddit already exists
existing_multis = list(reddit.user.me().multireddits())
multi = next((m for m in existing_multis if m.name == MULTI_NAME), None)

if multi:
    print(f"Multireddit '{MULTI_NAME}' already exists. Updating it...")
    multi.delete()
    print(f"Deleted multireddit '{MULTI_NAME}'.")

else:
    print(f"Creating new multireddit '{MULTI_NAME}'...")
    multi = reddit.multireddit.create(display_name=MULTI_NAME, subreddits=[])

successes=0
# Add subreddits to multireddit
for name in sub_names:
    try:
        multi.add(reddit.subreddit(name))
        print(f"✔ Added: {name}")
        successes += 1
    except Exception as e:
        print(f"✘ Failed to add {name}: {e}")
        break
print(f"\n{successes} new subreddit(s) added.")
