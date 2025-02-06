#!/bin/bash

# Check if a commit message was provided
if [ -z "$1" ]; then
    echo "❌ No commit message provided."
    echo "Usage: ./git_push.sh \"Your commit message\""
    exit 1
fi

# Define the branch name (default to main)
BRANCH=$(git rev-parse --abbrev-ref HEAD)

# Add all changes
echo "➕ Staging all changes..."
git add .

# Commit changes
echo "📝 Committing with message: \"$1\""
git commit -m "$1"

# Push to the remote repository
echo "🚀 Pushing to branch: $BRANCH"
git push origin "$BRANCH"

echo "✅ Push successful!"
