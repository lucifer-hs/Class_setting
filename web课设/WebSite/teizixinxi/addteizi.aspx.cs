﻿using System;
using System.Data.SqlClient;
using System.Web.UI;

public partial class addteizi : Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["UserName"] == null && Session["UserPwd"] == null)
        {
            Response.Redirect("~/denglu/denglu.aspx");
        }
        else
        {
            lblyhm.Text = Session["UserName"].ToString();
        }
    }

    protected void Button2_Click(object sender, EventArgs e)
    {
        SqlConnection con = DB.createDB();
        SqlCommand cmd = new SqlCommand();
        cmd.Connection = con;
        con.Open();
        cmd.CommandText =
            "insert into tb_Content(Subject,Words,UserName,CreateTime,LastAnswerTime,HitCount,IsTop,UpperId) values('" +
            txtbt.Text + "','" + txtnr.Text + "','" + lblyhm.Text + "','" + DateTime.Now.ToString() + "','" +
            DateTime.Now.ToString() + "','0','0','0')";
        cmd.ExecuteNonQuery();
        Response.Redirect("~/tisixinxi/chenggong.aspx");
        Response.Write("<script language=javascript>alert('恭喜您，信息添加成功！！');</script>");
        con.Close();
    }

    protected void LinkButton1_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Default.aspx");
    }

    protected void LinkButton3_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/dangqianxinxi/dqyhxinxixg.aspx");
    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        txtbt.Text = "";
        txtnr.Text = "";
    }

    protected void LinkButton5_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/yonghuxinxi/yonghuchaxun.aspx");
    }

    protected void LinkButton4_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/denglu/denglu.aspx");
    }

    protected void lbtnsy_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Default.aspx");
    }

    protected void ImageButton2_Click(object sender, ImageClickEventArgs e)
    {
        Response.Redirect("~/teizixinxi/addteizi.aspx");
    }
}