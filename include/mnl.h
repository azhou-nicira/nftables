#ifndef _NFTABLES_MNL_H_
#define _NFTABLES_MNL_H_

#include <list.h>

struct mnl_socket;

uint32_t mnl_seqnum_alloc(void);
void mnl_genid_get(struct mnl_socket *nf_sock);

struct mnl_err {
	struct list_head	head;
	int			err;
	uint32_t		seqnum;
};

void mnl_err_list_free(struct mnl_err *err);

struct nftnl_batch *mnl_batch_init(void);
bool mnl_batch_ready(struct nftnl_batch *batch);
void mnl_batch_reset(struct nftnl_batch *batch);
uint32_t mnl_batch_begin(struct nftnl_batch *batch);
void mnl_batch_end(struct nftnl_batch *batch);
int mnl_batch_talk(struct mnl_socket *nl, struct nftnl_batch *batch,
		   struct list_head *err_list);
int mnl_nft_rule_batch_add(struct nftnl_rule *nlr, struct nftnl_batch *batch,
			   unsigned int flags, uint32_t seqnum);
int mnl_nft_rule_batch_del(struct nftnl_rule *nlr, struct nftnl_batch *batch,
			   unsigned int flags, uint32_t seqnum);
int mnl_nft_rule_batch_replace(struct nftnl_rule *nlr, struct nftnl_batch *batch,
			       unsigned int flags, uint32_t seqnum);

int mnl_nft_rule_add(struct mnl_socket *nf_sock, struct nftnl_rule *r,
		     unsigned int flags);
int mnl_nft_rule_delete(struct mnl_socket *nf_sock, struct nftnl_rule *r,
			unsigned int flags);
struct nftnl_rule_list *mnl_nft_rule_dump(struct mnl_socket *nf_sock,
					int family);

int mnl_nft_chain_add(struct mnl_socket *nf_sock, struct nftnl_chain *nlc,
		      unsigned int flags);
int mnl_nft_chain_batch_add(struct nftnl_chain *nlc, struct nftnl_batch *batch,
			    unsigned int flags, uint32_t seq);
int mnl_nft_chain_delete(struct mnl_socket *nf_sock, struct nftnl_chain *nlc,
                         unsigned int flags);
int mnl_nft_chain_batch_del(struct nftnl_chain *nlc, struct nftnl_batch *batch,
			    unsigned int flags, uint32_t seq);
struct nftnl_chain_list *mnl_nft_chain_dump(struct mnl_socket *nf_sock,
					  int family);
int mnl_nft_chain_get(struct mnl_socket *nf_sock, struct nftnl_chain *nlc,
		      unsigned int flags);

int mnl_nft_table_add(struct mnl_socket *nf_sock, struct nftnl_table *nlt,
		      unsigned int flags);
int mnl_nft_table_batch_add(struct nftnl_table *nlt, struct nftnl_batch *batch,
			    unsigned int flags, uint32_t seq);
int mnl_nft_table_delete(struct mnl_socket *nf_sock, struct nftnl_table *nlt,
			 unsigned int flags);
int mnl_nft_table_batch_del(struct nftnl_table *nlt, struct nftnl_batch *batch,
			    unsigned int flags, uint32_t seq);
struct nftnl_table_list *mnl_nft_table_dump(struct mnl_socket *nf_sock,
					  int family);
int mnl_nft_table_get(struct mnl_socket *nf_sock, struct nftnl_table *nlt,
		      unsigned int flags);

int mnl_nft_set_add(struct mnl_socket *nf_sock, struct nftnl_set *nls,
		    unsigned int flags);
int mnl_nft_set_batch_add(struct nftnl_set *nls, struct nftnl_batch *batch,
			  unsigned int flags, uint32_t seq);
int mnl_nft_set_delete(struct mnl_socket *nf_sock, struct nftnl_set *nls,
		       unsigned int flags);
int mnl_nft_set_batch_del(struct nftnl_set *nls, struct nftnl_batch *batch,
			  unsigned int flags, uint32_t seq);
struct nftnl_set_list *mnl_nft_set_dump(struct mnl_socket *nf_sock, int family,
				      const char *table);
int mnl_nft_set_get(struct mnl_socket *nf_sock, struct nftnl_set *nls);

int mnl_nft_setelem_add(struct mnl_socket *nf_sock, struct nftnl_set *nls,
			unsigned int flags);
int mnl_nft_setelem_batch_add(struct nftnl_set *nls, struct nftnl_batch *batch,
			      unsigned int flags, uint32_t seq);
int mnl_nft_setelem_delete(struct mnl_socket *nf_sock, struct nftnl_set *nls,
			   unsigned int flags);
int mnl_nft_setelem_batch_del(struct nftnl_set *nls, struct nftnl_batch *batch,
			      unsigned int flags, uint32_t seq);
int mnl_nft_setelem_batch_flush(struct nftnl_set *nls, struct nftnl_batch *batch,
				unsigned int flags, uint32_t seqnum);
int mnl_nft_setelem_get(struct mnl_socket *nf_sock, struct nftnl_set *nls);

struct nftnl_obj_list *mnl_nft_obj_dump(struct mnl_socket *nf_sock, int family,
					const char *table, const char *name,
					uint32_t type, bool dump, bool reset);
int mnl_nft_obj_batch_add(struct nftnl_obj *nln, struct nftnl_batch *batch,
			  unsigned int flags, uint32_t seqnum);
int mnl_nft_obj_batch_del(struct nftnl_obj *nln, struct nftnl_batch *batch,
			  unsigned int flags, uint32_t seqnum);

struct nftnl_ruleset *mnl_nft_ruleset_dump(struct mnl_socket *nf_sock,
					 uint32_t family);
int mnl_nft_event_listener(struct mnl_socket *nf_sock,
			   int (*cb)(const struct nlmsghdr *nlh, void *data),
			   void *cb_data);

bool mnl_batch_supported(struct mnl_socket *nf_sock);

#endif /* _NFTABLES_MNL_H_ */
