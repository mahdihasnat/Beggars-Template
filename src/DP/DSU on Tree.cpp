vector<int> *pvec[MAX];
vector<int> G[MAX];
int sz[MAX],color[MAX],color_counter[MAX];
pair<ll,int> Info[MAX];
pair<ll,int>dfs(int u,int p=-1,bool keep=false)
{
    int i,j,k,child,hchild=-1;
    for(i=0; i<G[u].size(); i++)
    {
        if(G[u][i]==p) continue;
        if(hchild==-1||sz[hchild]<sz[G[u][i]])
        {
            hchild=G[u][i];
        }
    }
    for(i=0; i<G[u].size(); i++)
    {
        if(G[u][i]==p||G[u][i]==hchild) continue;
        dfs(G[u][i],u,false);
    }
    if(hchild!=-1)
    {
        Info[u]=dfs(hchild,u,true);
        pvec[u]=pvec[hchild];
    }
    else
    {
        pvec[u]=new vector<int> ();
    }
    pvec[u]->push_back(u);
    color_counter[color[u]]++;
    if(color_counter[color[u]]>Info[u].second)
    {
        Info[u].second=color_counter[color[u]];
        Info[u].first=color[u];
    }
    else if(color_counter[color[u]]==Info[u].second)
    {
        Info[u].first=Info[u].first+color[u];
    }
    for(i=0; i<G[u].size(); i++)
    {
        if(G[u][i]==p||G[u][i]==hchild) continue;
        child=G[u][i];
        for(j=0; j<(*pvec[child]).size(); j++)
        {
            k=(*pvec[child])[j];
            pvec[u]->push_back(k);
            color_counter[color[k]]++;
            if(color_counter[color[k]]>Info[u].second)
            {
                Info[u].second=color_counter[color[k]];
                Info[u].first=color[k];
            }
      else if(color_counter[color[k]]==Info[u].second)
            {
                Info[u].first=Info[u].first+color[k];
            }
        }
    }
    if(!keep)
    {
        for(j=0; j<(*pvec[u]).size(); j++)
        {
            k=(*pvec[u])[j];
            color_counter[color[k]]--;
        }
    }
    return Info[u];
}