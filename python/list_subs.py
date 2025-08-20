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
for sub in subreddits:
    print(f"- {sub.display_name}")
print(f"\nYou're subscribed to {len(subreddits)} subreddits:\n")
