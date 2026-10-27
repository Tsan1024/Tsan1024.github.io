import { defineCollection } from 'astro:content';
import { glob } from 'astro/loaders';
import { z } from 'astro/zod';

const blog = defineCollection({
	// Keep posts portable: plain Markdown only.
	loader: glob({ base: './src/content/blog', pattern: '**/*.md' }),
	// Type-check frontmatter using a schema
	schema: ({ image }) =>
		z.object({
			title: z.string(),
			description: z.string(),
			// Transform string to Date object
			pubDate: z.coerce.date(),
			updatedDate: z.coerce.date().optional(),
			tags: z.array(z.string()).default([]),
			draft: z.boolean().default(false),
		}),
});

const bookmarks = defineCollection({
	loader: glob({ base: './src/content/bookmarks', pattern: '**/*.md' }),
	schema: z.object({
		title: z.string(),
		url: z.url().refine((value) => /^https?:\/\//.test(value), 'Use an HTTP or HTTPS link'),
		author: z.string(),
		topic: z.string(),
		date: z.coerce.date(),
	}),
});

export const collections = { blog, bookmarks };
